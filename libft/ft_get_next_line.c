/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:07:22 by pmelis            #+#    #+#             */
/*   Updated: 2023/11/24 20:07:25 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#new_line():	reads from a file descriptor fd into a buffer and concatenates
				it with static_buffer until a newline character is found in
				static_buffer or the end of the file is reached.

#Parameters:	int fd
				char *static_buffer

#Return value:	char *static_buffer

#How it works:	first it allocates memory for buffer using BUFFER_SIZE + 1.
				while static_buffer doesn't have \n and size != 0 (end of ln)
				set size == read bytes from fd to buffer. if error occurs (-1)
				free buffers and return null. terminate buffer \0 and sets
				static_buffer += buffer. finally frees the buffer and returns
				static_buffer.
*/

char	*new_line(int fd, char *static_buffer)
{
	char	*buffer;
	int		size;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	size = 1;
	while (!ft_strchr(static_buffer, '\n') && size != 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == -1)
		{
			free(static_buffer);
			free(buffer);
			return (NULL);
		}
		buffer[size] = '\0';
		static_buffer = ft_strjoin(static_buffer, buffer);
	}
	free(buffer);
	return (static_buffer);
}

/*
#fixed_line():	cleans up the static buffer until \n or \0

#Parameters:	char *static_buffer

#Return value:	char *line

#How it works:	if static_buffer is empty, return null. using a while loop, set
				i == length of static buffer line (until end or \n). afterwards
				it allocates memory for the line using i + 2 (\n\0). using the
				same conditions on a while loop, set line == static buffer. if
				there is a \n at the end copy it to line, and finally finish it
				with \0 and return it.

*/

char	*fixed_line(char *static_buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!static_buffer[i])
		return (NULL);
	while (static_buffer[i] && static_buffer[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
	{
		line[i] = static_buffer[i];
		i++;
	}
	if (static_buffer[i] == '\n')
	{
		line[i] = static_buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/*
#next_line():	returns remaining chr after \n and frees static_buffer

#Parameters:	char *static_buffer

#Return value:	char *next

#How it works:	first i == len of static_buffer line. if it reached \0 (eof)
				free static_buffer and return null. then it allocates memory
				for *next using (total len) - (len before \n) + 1. then it
				copies remaining static_buffer after \n into *next and finally
				terminates \0 *next and frees the static buffer and returns next
*/

char	*next_line(char *static_buffer)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
		i++;
	if (!static_buffer[i])
	{
		free(static_buffer);
		return (NULL);
	}
	next = malloc(sizeof(char) * (ft_strlen(static_buffer) - i + 1));
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (static_buffer[i])
		next[j++] = static_buffer[i++];
	next[j] = '\0';
	free(static_buffer);
	return (next);
}

/*
#get_next_line():	Write a function that returns a line read from a
					file descriptor.

#Parameters:		int fd

#Return value:		char *ln -- line read

#How it works:		Only difference = sets the size of static_buffer to 10240
					first input checks, then it sets static_buffer to the line
					read, if static buffer == \0 return null. set ln to the new
					formated line, set static buffer with remaining bytes read
					and finally return ln.
*/

char	*get_next_line(int fd)
{
	char		*ln;
	static char	*static_buffer[20000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	static_buffer[fd] = new_line(fd, static_buffer[fd]);
	if (!static_buffer[fd])
		return (NULL);
	ln = fixed_line(static_buffer[fd]);
	static_buffer[fd] = next_line(static_buffer[fd]);
	return (ln);
}
