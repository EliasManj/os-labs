
// GCC provides these header files automatically
// They give us access to useful things like fixed-width types
#include <stddef.h>
#include <stdint.h>

// First, let's do some basic checks to make sure we are using our x86-elf cross-compiler correctly
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif
//Color support
#define BLACK 						0x00
#define BLUE 							0x01
#define GREEN 						0x00
#define CYAN 							0x03
#define RED 							0x04
#define MAGENTA 					0x05
#define BROWN 						0x06
#define LIGHT_GRAY 				0x07
#define DARK_GRAY 				0x08
#define LIGHT_BLUE 				0x09
#define LIGHT_GREEN 			0x0A
#define LIGHT_CYAN 				0x0B
#define LIGHT_RED 				0x0C
#define LIGH_MAGENTA 			0x0D
#define YELLOW 						0x0E
#define WHITE 						0x0F


// This is the x86's VGA textmode buffer. To display text, we write data to this memory location
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
// By default, the VGA textmode buffer has a size of 80x25 characters
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

// We start displaying text in the top-left of the screen (column = 0, row = 0)
int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x9F; // Black background, White foreground

// This function initiates the terminal by clearing it
void term_init(uint16_t color_background, uint16_t color_foreground)
{
	uint16_t color_format;
	color_format = (color_background<<4)+color_foreground;
	// Clear the textmode buffer
	for (int col = 0; col < VGA_COLS; col ++)
	{
		for (int row = 0; row < VGA_ROWS; row ++)
		{
			// The VGA textmode buffer has size (VGA_COLS * VGA_ROWS).
			// Given this, we find an index into the buffer for our character
			const size_t index = (VGA_COLS * row) + col;
			// Entries in the VGA buffer take the binary form BBBBFFFFCCCCCCCC, where:
			// - B is the background color
			// - F is the foreground color
			// - C is the ASCII character
			vga_buffer[index] = ((uint16_t)color_format << 8) | ' '; // Set the character to blank (a space character)
		}
	}
}

// This function places a single character onto the screen
void term_putc(char c, uint16_t color)
{
	// Remember - we don't want to display ALL characters!
	switch (c)
	{
	case '\n': // Newline characters should return the column to 0, and increment the row
		{
			term_col = 0;
			term_row ++;
			break;
		}

	default: // Normal characters just get displayed and then increment the column
		{
			const size_t index = (VGA_COLS * term_row) + term_col; // Like before, calculate the buffer index
			vga_buffer[index] = ((uint16_t)color << 8) | c;
			term_col ++;
			break;
		}
	}

	// What happens if we get past the last column? We need to reset the column to 0, and increment the row to get to a new line
	if (term_col >= VGA_COLS)
	{
		term_col = 0;
		term_row ++;
	}

	// What happens if we get past the last row? We need to reset both column and row to 0 in order to loop back to the top of the screen
	if (term_row >= VGA_ROWS)
	{
		term_col = 0;
		term_row = 0;
	}
}

// This function prints an entire string onto the screen
void term_print(const char* str, uint16_t color_background, uint16_t color_foreground)
{
	uint16_t color_format;
	color_format = (color_background<<4)+color_foreground;
	for (size_t i = 0; str[i] != '\0'; i ++) // Keep placing characters until we hit the null-terminating character ('\0')
		term_putc(str[i], color_format);
}



// This is our kernel's main function
void kernel_main()
{
	// We're here! Let's initiate the terminal and display a message to show we got here.

	// Initiate terminal
	term_init(LIGHT_BLUE, WHITE);

	// Display some messages
	term_print("Hello, World!\n", LIGHT_BLUE, BLACK);
	term_print("Welcome to the kernel.\n", LIGHT_BLUE, RED);
	term_print("This terminal has color support\n", LIGHT_BLUE, LIGH_MAGENTA);

}
