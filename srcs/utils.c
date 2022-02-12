#include "kernel.h"
#include "keyboard.h"
#include "utils.h"

void print_next_line()
{
  if (next_line_index >= 25){
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  }
  vga_index = 80 * next_line_index++;
}

void print_char(char ch)
{
  vga_buffer[vga_index++] = vga_entry(ch, g_fore_color, g_back_color);
}


void bzero(void *buf, uint32 n)
{
  while(n - 1 < n)
    ((char *)buf)[--n] = 0;
}

uint32 strlen(const char *str)
{
  if (!str)
    return 0;
  uint32 len = 0;
  while (str[len])
    ++len;
  return len;
}

uint32 digit_count(int num)
{
  uint32 count = 0;
  if (!num)
    return 1;
  while (num > 0)
  {
    ++count;
    num /= 10;
  }
  return count;
}


void itoa(int num, char *number)
{
  int digits = digit_count(num);
  int index = digits - 1;
  if (num == 0 && digits == 1) {
    number[0] = '0';
    number[1] = 0;
  } else {
    while (num != 0){
      number[index--] = num%10 + '0';
      num = num / 10;
    }
    number[digits] = 0;
  }
  return;
}

void print_string(char *str)
{
  if (!str)
    return ;
  uint32 index = 0;
  while (str[index])
    print_char(str[index++]);
}

void print_int(int num)
{
  char str_num[digit_count(num) + 1];
  itoa(num, str_num);
  print_string(str_num);
}

char get_ascii_char(uint16 keycode)
{
  return kbd_US[keycode];
}

void add_to_buf(char c)
{
  if (screens[curscreen].inp_ind >= 255)
    return;
  screens[curscreen].inp_buf[screens[curscreen].inp_ind] = c;
  screens[curscreen].inp_ind++;
}
