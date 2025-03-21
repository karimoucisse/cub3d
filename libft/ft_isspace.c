int	ft_isspace(int c)
{
	if (c == 12 || c == 10 || c == 13 || c == 9 || c == 11 || c == 32)
		return (1);
	return (0);
}
