import rclpy
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from builtin_interfaces.msg import Duration
import sys, tty, termios, select

class TeleopJoints(Node):
    def __init__(self):
        super().__init__('teleop_joints')
        
        self.joint_names = ['1', '2', '3', '4', '5', '6']
        self.positions = [0.0] * 6
        self.selected_joint_index = 0
        self.step_size = 0.1
        
        self.publisher = self.create_publisher(JointTrajectory, '/lerobot_controller/joint_trajectory', 10)
        
        self.get_logger().info("Teleop de Joints iniciado.")
        self.print_instructions()
        self.publish_trajectory()

    def print_instructions(self):
        print("\n--- CONTROL DE JOINTS ---")
        print("Seleccionar Joint: Teclas 1 - 6")
        print("Mover: 'w' (Subir/+)  's' (Bajar/-)")
        print("Salir: 'q' o Ctrl+C")
        print("-------------------------")

    def get_key(self):
        """Lee una tecla solo si está disponible, sin bloquear"""
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            # Usar select para esperar solo 0.1 segundos
            i_ready, _, _ = select.select([sys.stdin], [], [], 0.1)
            if i_ready:
                ch = sys.stdin.read(1)
            else:
                ch = None
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

    def publish_trajectory(self):
        msg = JointTrajectory()
        msg.joint_names = self.joint_names
        
        point = JointTrajectoryPoint()
        point.positions = self.positions
        point.velocities = [0.0] * 6
        point.time_from_start = Duration(sec=2, nanosec=0)
        
        msg.points.append(point)
        self.publisher.publish(msg)
        
        status = f"Joint Activo: [{self.joint_names[self.selected_joint_index]}] | Pos: {self.positions[self.selected_joint_index]:.2f}"
        print(f"\r{status}", end='', flush=True)

    def run_loop(self):
        try:
            while rclpy.ok():
                # 1. Procesar eventos de ROS (vital para publicar)
                rclpy.spin_once(self, timeout_sec=0.01)
                
                # 2. Leer teclado (no bloqueante gracias a get_key)
                key = self.get_key()
                
                if key is None:
                    continue # No hay tecla, volver a spin_once
                
                if key == 'q':
                    break
                elif key in ['1', '2', '3', '4', '5', '6']:
                    self.selected_joint_index = int(key) - 1
                    self.print_status_only()
                elif key == 'w':
                    self.positions[self.selected_joint_index] += self.step_size
                    self.publish_trajectory()
                elif key == 's':
                    self.positions[self.selected_joint_index] -= self.step_size
                    self.publish_trajectory()
                    
        except KeyboardInterrupt:
            pass
        finally:
            self.destroy_node()

    def print_status_only(self):
        status = f"Joint Activo: [{self.joint_names[self.selected_joint_index]}] | Pos: {self.positions[self.selected_joint_index]:.2f}"
        print(f"\r{status}", end='', flush=True)

def main(args=None):
    rclpy.init(args=args)
    node = TeleopJoints()
    node.run_loop()
    rclpy.shutdown()

if __name__ == '__main__':
    main()   