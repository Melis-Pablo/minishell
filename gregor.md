# Welcome Gregor to the Minishell Project

## Introduction MINIHELL

## Project Structure

The project is structured as follows:

- `srcs/`: Contains the source code of the project.
  - `cleanup/`: Contains the cleanup functions.
  - `parsing/`: Contains the parsing functions.
  - `utils/`: Contains utility functions.
- `includes/`: Contains the header files.
- `extras/`: Contains extra files like prompts and samples.
- `Makefile`: Used to compile the project.
- `README.md`: Contains the project documentation.

## PseudoCode

1. main()
	- input = readline()
	>Cmd1 -flag0 --flag1 arg1 "arg | 2" <infile.txt < infile1.txt <<heredoc1 | Cmd2 -flag2 --flag21 arg21 "arg | 22" <infile2.txt < infile_2.txt << heredoc2 | Cmd3 -flag3 --flag31 arg31 "arg | 23" <infile4.txt < infile5.txt <<heredoc3 > outfile.txt >>append3.txt << heredoc33
2. Cmd_lst_builder()
	- command_strings = Split_by_pipes(input)
	>command_strings[0] = Cmd1 -flag0 --flag1 arg1 "arg | 2" <infile.txt < infile1.txt <<heredoc1 

	>command_strings[1] = Cmd2 -flag2 --flag21 arg21 "arg | 22" <infile2.txt < infile_2.txt << heredoc2 

	>command_strings[2] = Cmd3 -flag3 --flag31 arg31 "arg | 23" <infile4.txt < infile5.txt <<heredoc3 > outfile.txt >>append3.txt << heredoc33
	- while (command_strings[i])
		- words = split_into_words(command_strings[i])
		- cmd_node = build_node(words)
		- add_to_lst(cmd_node)
	- return (head node);
	- (expand environmental variables at some point)

```c
struct s_cmd [0]
{
	char			*cmd; [Cmd1]
	char			**args; [-flag0, --flag1]
	char			**flags; [arg1, "arg | 2"]
	char			**infile; [infile.txt, infile1.txt]
	char			**outfile; [null]
	char			**delimiter; [heredoc1]
	char			**append; [null]
	struct s_cmd	*prev; [null]
	struct s_cmd	*next; [node[1]]
}					t_cmd;

struct s_cmd [1]
{
	char			*cmd; [Cmd2]
	char			**args; [arg21 "arg | 22"]
	char			**flags; [-flag2, --flag21]
	char			**infile; [infile2.txt, infile_2.txt ]
	char			**outfile; [null]
	char			**delimiter; [heredoc2]
	char			**append; [null]
	struct s_cmd	*prev; [node[1]]
	struct s_cmd	*next; [node[2]]
}					t_cmd;

struct s_cmd [2]
{
	char			*cmd; [Cmd3]
	char			**args; [arg31, "arg | 23"]
	char			**flags; [-flag3, --flag31]
	char			**infile; [infile4.txt, infile5.txt]
	char			**outfile; [outfile.txt]
	char			**delimiter; [heredoc3, heredoc33]
	char			**append; [append3.txt]
	struct s_cmd	*prev; [node[1]]
	struct s_cmd	*next; [null]
}					t_cmd;
```

3. loop through each node
	- redirect properly
	- execute properly (also built ins)
