/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:53:54 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/05/08 14:55:36 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_costume_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*p;

	i = ft_strlen(s1);
	if (i == 0)
		return (NULL);
	j = 0;
	p = (char *)ft_calloc(i + 1, 1);
	if (p == NULL)
		return (NULL);
	while (j < i + 1)
	{
		p[j] = s1[j];
		j++;
	}
	return (p);
}

char	*ft_get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		line[100000];
	static int	bufread;
	static int	bufpose;
	int			i;

	i = 0;
	while (1)
	{
		if (bufread == bufpose)
		{
			bufread = read(fd, buf, BUFFER_SIZE);
			bufpose = 0;
			if (!bufread)
				break ;
			buf[bufread] = '\0';
		}
		line[i++] = buf[bufpose++];
		if (buf[bufpose - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	return (ft_costume_strdup(line));
}
