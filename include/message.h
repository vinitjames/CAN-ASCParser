#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <vector>

struct Message {
  Message() = default;
  Message(Message& other) = default;
  Message(Message&& other) noexcept;
  Message& operator=(Message& other) = default;
  Message& operator=(Message&& other) noexcept;

  void arbitration_id(int id);
  int arbitration_id() const;

  void bit_rate_switch(bool bit_rate_switch);
  bool bit_rate_switch() const;

  void channel(int channel);
  int channel() const;

  void dlc(int dlc);
  int dlc() const;

  void error_state_indicator(bool err_state_ind);
  bool error_state_indicator() const;

  void is_error_frame(bool is_error_frame);
  bool is_error_frame() const;

  void is_extended(bool is_extended);
  bool is_extended() const;

  void is_fd(bool is_fd);
  bool is_fd() const;

  void is_remote_frame(bool is_remote_frame);
  bool is_remote_frame() const;

  void is_rx(bool is_rx);
  bool is_rx() const;

  void timestamp(double timestamp);
  double timestamp() const;

  void data(std::vector<uint8_t>&& data);
  const std::vector<uint8_t>& data() const;

 private:
  double _timestamp = 0.0;
  int _arbitration_id = 0;
  bool _is_extended_id = false;
  bool _is_remote_frame = false;
  bool _is_error_frame = false;
  int _channel = 0;
  int _dlc = 0;
  bool _is_fd = false;
  bool _is_rx = false;
  bool _bit_rate_switch = false;
  bool _error_state_indicator = false;
  std::vector<uint8_t> _data;
};

#endif /* MESSAGE_H */
