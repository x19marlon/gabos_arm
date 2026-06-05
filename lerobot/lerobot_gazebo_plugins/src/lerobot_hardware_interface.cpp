#include "lerobot_gazebo_plugins/lerobot_hardware_interface.hpp"
#include "pluginlib/class_list_macros.hpp"
#include <memory>


namespace lerobot_hardware_interface {

//------------------------------------------------------------------------------
// Gazebo life cycle configuration
//------------------------------------------------------------------------------


// Initial configuration to gazebo.
bool LerobotHardwareInterface::initSim(rclcpp::Node::SharedPtr &model_nh,
                                       std::map<std::string, sim::Entity> &joints,
                                       const hardware_interface::HardwareInfo &/*hardware_info*/,
                                       sim::EntityComponentManager &ecm,
                                       unsigned int /*update_rate*/) {
    nh_ = model_nh;
    ecm_ = &ecm;
    enable_joints_ = joints;

    // Personified parameters loader:
    // loadParameters(hardware_info);

    gz_node_ = std::make_unique<gz::transport::Node>();
    // actuators_pub_ = gz_node_->Advertise<gz::msgs::Actuators>(actuators_topic_);

    return true;
}

//------------------------------------------------------------------------------
// Hardware interface life cycle configuration
//------------------------------------------------------------------------------

// Initialization of all members variables and process parameters from the params argument.
hardware_interface::CallbackReturn LerobotHardwareInterface::on_init(
    const hardware_interface::HardwareComponentInterfaceParams & params) {

    if (
        hardware_interface::SystemInterface::on_init(params) !=
        hardware_interface::CallbackReturn::SUCCESS)
    {
        return hardware_interface::CallbackReturn::ERROR;
    }


    return hardware_interface::CallbackReturn::SUCCESS;
}

// Setup of the communication to the hardware and set everything up so that the hardware can be activated.
hardware_interface::CallbackReturn LerobotHardwareInterface::on_configure(
    const rclcpp_lifecycle::State & /*previous_state*/) {



    return hardware_interface::CallbackReturn::SUCCESS;
}

// Opposite of on_configure method.
hardware_interface::CallbackReturn LerobotHardwareInterface::on_cleanup(
    const rclcpp_lifecycle::State & /*previous_state*/) {



    return hardware_interface::CallbackReturn::SUCCESS;
}

// Hardware "power" is enabled.
hardware_interface::CallbackReturn LerobotHardwareInterface::on_activate(
    const rclcpp_lifecycle::State & /*previous_state*/) {

    RCLCPP_INFO(get_logger(), "Activating... please wait...");


    RCLCPP_INFO(get_logger(), "Successfully activated! :D");

    return hardware_interface::CallbackReturn::SUCCESS;
}

// Hardware "power" is disabled.
hardware_interface::CallbackReturn LerobotHardwareInterface::on_deactivate(
    const rclcpp_lifecycle::State & /*previous_state*/) {

    RCLCPP_INFO(get_logger(), "Deactivating... please wait...");


    RCLCPP_INFO(get_logger(), "Successfully deactivated! :D");

    return hardware_interface::CallbackReturn::SUCCESS;
}

// Hardware is shutdown.
hardware_interface::CallbackReturn LerobotHardwareInterface::on_shutdown(
    const rclcpp_lifecycle::State & previous_state) {


    return on_cleanup(previous_state);
}

//------------------------------------------------------------------------------
// Hardware interface telemetry
//------------------------------------------------------------------------------

hardware_interface::return_type LerobotHardwareInterface::read(
    const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/) {

    return hardware_interface::return_type::OK;
}

hardware_interface::return_type LerobotHardwareInterface::write(
    const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/) {

    return hardware_interface::return_type::OK;
}

}

PLUGINLIB_EXPORT_CLASS(lerobot_hardware_interface::LerobotHardwareInterface,
                       gz_ros2_control::GazeboSimSystemInterface)