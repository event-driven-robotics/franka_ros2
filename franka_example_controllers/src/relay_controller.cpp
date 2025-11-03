#include "franka_example_controllers/relay_controller.hpp"
#include "pluginlib/class_list_macros.hpp"

namespace franka_example_controllers
{
RelayController::RelayController() = default;

controller_interface::CallbackReturn RelayController::on_init()
{
  try
  {
    subscriber_ = get_node()->create_subscription<JointCommandMsg>
            (
                "joint_command_relay",                                                                   // Name of topic to subscribe to
                1,                                                                                  // No. of msgs to retain
                std::bind(&RelayController::relay, this, std::placeholders::_1)                   // Callback function for when message is received
            );

    RCLCPP_INFO(get_node()->get_logger(), "RelayController initialized.");
  }
  catch (const std::exception &e)
  {
    RCLCPP_ERROR(get_node()->get_logger(), "Exception during initialization: %s", e.what());
    return controller_interface::CallbackReturn::ERROR;
  }
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn RelayController::on_configure(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(get_node()->get_logger(), "RelayController configured.");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn RelayController::on_activate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(get_node()->get_logger(), "RelayController activated.");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn RelayController::on_deactivate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(get_node()->get_logger(), "RelayController deactivated.");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::return_type RelayController::update(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{
  // RCLCPP_INFO(get_node()->get_logger(), "Setting command: %f", command_);
  return controller_interface::return_type::OK;
}

controller_interface::InterfaceConfiguration RelayController::command_interface_configuration() const
{
  controller_interface::InterfaceConfiguration config;
  config.type = controller_interface::interface_configuration_type::NONE;
  return config;
}

controller_interface::InterfaceConfiguration RelayController::state_interface_configuration() const
{
  controller_interface::InterfaceConfiguration config;
  config.type = controller_interface::interface_configuration_type::NONE;
  return config;
}

void RelayController::relay(const JointCommandMsg::SharedPtr msg){
    command_ = msg->command[0]; // Assuming single joint command for simplicity
    RCLCPP_INFO(get_node()->get_logger(), "Received command: %f", command_);
}
}  // namespace franka_example_controllers

PLUGINLIB_EXPORT_CLASS(franka_example_controllers::RelayController, controller_interface::ControllerInterface)