#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool is_on_stack(void *ptr) {
  void *stack_top = __builtin_frame_address(0);
  uintptr_t stack_top_addr = (uintptr_t)stack_top;
  uintptr_t ptr_addr = (uintptr_t)ptr;

  // Check within a threshold in both directions (e.g., 1MB)
  uintptr_t threshold = 1024;

  return ptr_addr >= (stack_top_addr - threshold) && ptr_addr <= (stack_top_addr + threshold);
}

char *get_full_sentence(char *sentence_one, char *sentence_two, int size) {
  char *full_sentence = (char*)malloc(size*sizeof(char));
  snprintf(full_sentence, size, "%s %s", sentence_one, sentence_two);
  return full_sentence;
}

int main() {
    int on_stack = 100;
	printf("sentence_on_stack is on the stack: %s\n", is_on_stack(&on_stack)?"true":"false");

    char* sentence_on_heap = get_full_sentence("I am", " on the heap.", 20);
    printf("sentence_on_heap is on the stack: %s\n", is_on_stack(sentence_on_heap)?"true":"false");
    
    return 0;
}