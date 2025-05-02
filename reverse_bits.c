/*
Write a function that takes a byte, reverses it, bit by bit (like the
example) and returns the result.

Your function must be declared as follows:

unsigned char	reverse_bits(unsigned char octet);
*/

unsigned char	reverse_bits(unsigned char octet)
{
	int				i;
	unsigned char	rev;

	i = 7;
	while (i >= 0)
	{
		rev = (rev * 2) + (octet % 2);
		octet = octet / 2;
		i--;
	}
	return (rev);
}
// #include <unistd.h>
// void	print_bits(unsigned char octet)
// {
// 	int				i;
// 	unsigned char	bit;

// 	i = 7;
// 	while (i >= 0)
// 	{
// 		bit = ((octet >> i) & 1) + '0';
// 		write (1, &bit, 1);
// 		i--;
// 	}
// }

// int main()
// {
// 	unsigned char input = 38;
// 	unsigned char reversed = reverse_bits(input);

// 	write(1, "Input (binary):   ", 18);
// 	print_bits(input);
// 	write(1, "\n", 1);

// 	write(1, "Reverse (binary): ", 18);
// 	print_bits(reversed);
// 	write(1, "\n", 1);

// 	return 0;
// }