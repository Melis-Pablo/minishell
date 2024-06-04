/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:50:42 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/04 15:37:34 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Plan to build cmd list:

fuctions to be created:
1. check_cmd
2. check_args
3. check_flags
4. check_infile
5. check_outfile
6. check_delimiter
7. check_append
-------------------------
(should call check_* functions)
8. count_cmds
9. count_args
10. count_flags
11. count_infile
12. count_outfile
13. count_delimiter
14. count_append
-------------------------
(should call count_* functions)
15. get_cmds
16. get_args
17. get_flags
18. get_infile
19. get_outfile
20. get_delimiter
21. get_append
-------------------------
22. create_and_fill_cmd (should call get_* functions)
23. build_cmd_list (should call create_and_fill_cmd)


Pseudo code of build_cmd_list:
1. split the input by pipes
2. loop through the strings
3. create a new cmd
4. fill the cmd with the data
5. add the cmd to the list
6. return the list
*/

