/*
Write a function that takes a byte, swaps its halves (like the example) and
returns the result.

Your function must be declared as follows:

unsigned char	swap_bits(unsigned char octet);
*/

unsigned char	swap_bits(unsigned char octet)
{
	return ((octet >> 4 | octet << 4));
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
// #include <stdio.h>
// int main()
// {
// 	unsigned char octet = 00000001;
// 	print_bits(swap_bits(octet));
// 	return (0);
// }
