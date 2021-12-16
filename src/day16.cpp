#include "main.hpp"

std::uint64_t bitstring_value(std::string bits) {
  std::uint64_t value = 0;
  for (int i = 0; i < bits.size(); i++) {
    value +=
        bits[i] == '0' ? 0 : (std::uint64_t)std::pow(2, bits.size() - i - 1);
  }
  return value;
}

std::pair<int, int> parse_header(std::stringstream &bitstream,int &version_sum) {
  std::string version, type_id;
  version.push_back(bitstream.get());
  version.push_back(bitstream.get());
  version.push_back(bitstream.get());
  type_id.push_back(bitstream.get());
  type_id.push_back(bitstream.get());
  type_id.push_back(bitstream.get());
  version_sum += bitstring_value(version);
  return std::pair(bitstring_value(version), bitstring_value(type_id));
}

int parse_num(std::stringstream &bitstream) {
  char c = ' ';
  std::string num;
  while ((c = bitstream.get()) != '0') {
    num.push_back(bitstream.get());
    num.push_back(bitstream.get());
    num.push_back(bitstream.get());
    num.push_back(bitstream.get());
  }
  num.push_back(bitstream.get());
  num.push_back(bitstream.get());
  num.push_back(bitstream.get());
  num.push_back(bitstream.get());
  return bitstring_value(num);
}

std::pair<int, int> parse_op(std::stringstream &bitstream) {
  char length_type_id = bitstream.get();
  std::string num;
  if (length_type_id == '0') {
    for (int i = 0; i < 15; i++) {
      num.push_back(bitstream.get());
    }
  } else if (length_type_id == '1') {
    for (int i = 0; i < 11; i++) {
      num.push_back(bitstream.get());
    }
  }
  auto result = std::make_pair(0, 0);
  if (length_type_id == '0')
    result.first = bitstring_value(num);
  else
    result.second = bitstring_value(num);
  return result;
}

void parse_packet(std::stringstream& bitstream,int &version_sum) {
  
  auto [vers,t] = parse_header(bitstream,version_sum);
    std::cout << "Version: " << vers << " Type: " << t<<std::endl;
    if(t == 4) {
      auto num = parse_num(bitstream);
      std::cout << "Literal: " << num <<std::endl;
    } else {
      auto [len,count] = parse_op(bitstream);
      if(len > 0) {
        int pos = bitstream.tellg();
        int target = pos + len;
        while(pos < target) {
          parse_packet(bitstream,version_sum);
          pos = bitstream.tellg();
        }
      } else {
        for(int i = 0;i < count;i++) {
          parse_packet(bitstream,version_sum);
        }
      }
    }
  
}

void day16() {

  std::ifstream file("inputs/day16");
  std::string bitstring;
  while (file.good()) {

    char next = file.get();
    if (next == '0') {
      bitstring.append("0000");
    } else if (next == '1') {
      bitstring.append("0001");
    } else if (next == '2') {
      bitstring.append("0010");
    } else if (next == '3') {
      bitstring.append("0011");
    } else if (next == '4') {
      bitstring.append("0100");
    } else if (next == '5') {
      bitstring.append("0101");
    } else if (next == '6') {
      bitstring.append("0110");
    } else if (next == '7') {
      bitstring.append("0111");
    } else if (next == '8') {
      bitstring.append("1000");
    } else if (next == '9') {
      bitstring.append("1001");
    } else if (next == 'A') {
      bitstring.append("1010");
    } else if (next == 'B') {
      bitstring.append("1011");
    } else if (next == 'C') {
      bitstring.append("1100");
    } else if (next == 'D') {
      bitstring.append("1101");
    } else if (next == 'E') {
      bitstring.append("1110");
    } else if (next == 'F') {
      bitstring.append("1111");
    }
  }
  std::cout << bitstring << std::endl;

  std::stringstream stream(bitstring);
  int s = 0;
  parse_packet(stream,s);
  std::cout << "Day 16 => Part 1: " << s << std::endl;
}
