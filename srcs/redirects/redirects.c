/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:04:53 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/07 13:37:40 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Input Redirections (<)

    Multiple < Redirections:
        Example: command < infile1 < infile2
        Behavior: Only the last redirection is used, so the command will read
            input from infile2.
        Effect on First Ones: The first redirections (< infile1) have no effect
            They are ignored.

Output Redirections (> and >>)

    Multiple > Redirections:
        Example: command > outfile1 > outfile2
        Behavior: Only the last redirection is used, so the command will write
            to outfile2, truncating it before writing.
        Effect on First Ones: The first redirections (> outfile1) have no
            effect. They are ignored.

    Multiple >> Redirections:
        Example: command >> appendfile1 >> appendfile2
        Behavior: Only the last redirection is used, so the command will append
            to appendfile2.
        Effect on First Ones: The first redirections (>> appendfile1) have no
            effect. They are ignored.

	Mixing > and >>:
    	Example: command > outfile >> appendfile
    	Behavior: Only the last redirection is used. Here, the command will
            append to appendfile.
    	Effect on First Ones: The first redirection (> outfile) has no effect.
            It is ignored.

    	Example: command >> appendfile > outfile
    	Behavior: Only the last redirection is used. Here, the command will write
            to outfile, truncating it before writing.
    	Effect on First Ones: The first redirection (>> appendfile) has no effect
            It is ignored.

Here Document Redirections (<<)

    Mixing < and <<:
        < infile is used to redirect input from a file.
        << delimiter is used for here documents, where a block of text is
            provided directly in the command line until the delimiter is reached.

    Example: command < infile << EOF
        Behavior: The shell processes the input redirection (< infile) first,
            setting up the input from infile. The here document (<< EOF) is
            usually processed to provide input directly on the command line,
            which conflicts with reading from a file.
        Effect: the last one is used, but everything processed before that is
            ignored.
*/
