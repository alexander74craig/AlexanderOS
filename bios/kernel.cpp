extern "C" void main() 
{
    // Set location of start of the video memory.
    char* video_memory = reinterpret_cast<char*>(0xb8000);
    // Move down one line in video memory.
    video_memory += 160; 

    // Push message into video memory at the current location.
    char* string{"The kernel is running!\0"};
    for (int charIndex{0}; string[charIndex]; charIndex++)
    {
        *video_memory = string[charIndex];
        video_memory +=2;
    }
    return;
}