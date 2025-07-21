#ifndef BUFFER_H
#define BUFFER_H

std::vector<std::string> initialize_buffer();

void modify_buffer(int ch, std::vector<std::string> &buffer);

void print_buffer(const std::vector<std::string> &buffer);

#endif //BUFFER_H
