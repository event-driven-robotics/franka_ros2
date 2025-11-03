#ifndef FRANKA_EXAMPLE_CONTROLLERS_RELAY_CONTROLLER_HPP_
#define FRANKA_EXAMPLE_CONTROLLERS_RELAY_CONTROLLER_HPP_

#include "rclcpp/rclcpp.hpp"
#include "controller_interface/controller_interface.hpp"
#include "serial_link_interfaces/msg/joint_command.hpp"                                             // Custom message

using JointCommandMsg = serial_link_interfaces::msg::JointCommand;

namespace franka_example_controllers
{
class RelayController : public controller_interface::ControllerInterface
{
public:
  RelayController();

  controller_interface::CallbackReturn on_init() override;
  controller_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State &previous_state) override;
  controller_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State &previous_state) override;
  controller_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State &previous_state) override;
  controller_interface::return_type update(const rclcpp::Time &time, const rclcpp::Duration &period) override;

  controller_interface::InterfaceConfiguration command_interface_configuration() const override;  // Added
  controller_interface::InterfaceConfiguration state_interface_configuration() const override;    // Added

private:
  rclcpp::Subscription<JointCommandMsg>::SharedPtr subscriber_;
  void relay(const JointCommandMsg::SharedPtr msg);
  double command_;
};

}  // namespace franka_example_controllers

#endif  // FRANKA_EXAMPLE_CONTROLLERS_RELAY_CONTROLLER_HPP_