extern "C"
{

#include <stdint.h>

void main() 
{
    // Set location of start of the video memory.
    char* videoMemory = (char*)0xb8000;
    // Move down one line in video memory.
    videoMemory += 160; 

    // Push message into video memory at the current location.
    char* string{"The kernel is running!\0"};
    for (uint32_t charIndex{0}; string[charIndex]; charIndex++)
    {
        *videoMemory = string[charIndex];
        videoMemory +=2;
    }
    return;
}
}
