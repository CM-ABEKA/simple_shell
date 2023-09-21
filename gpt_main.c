#include "shell.h"

/* Global flag for Ctrl+C signal handling */
unsigned int ctrl_c_flag;

/**
 * sig_handler - Signal handler for Ctrl+C (^C) signal
 * @unused_arg: Unused argument (required by the signal function prototype)
 *
 * Handles Ctrl+C signals, resetting the prompt as needed.
 */
static void sig_handler(int unused_arg)
{
    (void)unused_arg;
    if (ctrl_c_flag == 0)
        _puts("\n$ ");
    else
        _puts("\n");
}

/**
 * main - Main function for the custom shell
 * @argc: Number of arguments passed to main (unused)
 * @argv: Array of arguments passed to main
 * @env: Array of environment variables
 *
 * Entry point for the custom shell program. Initializes variables, sets up
 * the Ctrl+C signal handler, and enters a loop to read and process commands.
 *
 * Return: 0 or exit status
 */
int main(int argc __attribute__((unused)), char **argv, char **env)
{
    size_t buf_size = 0;
    unsigned int is_pipe = 0;
    unsigned int i;
    vars_t svars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

    svars.argv = argv;
    svars.env = create_environment(env); /* Create environment variables */
    signal(SIGINT, sig_handler);         /* Set up Ctrl+C signal handler */

    if (!isatty(STDIN_FILENO)) /* Check if input is from a pipe */
        is_pipe = 1;

    ctrl_c_flag = 0;

    do
    {
        ctrl_c_flag = 1;
        svars.count++;
        svars.commands = tokenize(svars.buffer, ";");

        for (i = 0; svars.commands && svars.commands[i] != NULL; i++)
        {
            svars.av = tokenize(svars.commands[i], "\n \t\r");
            if (svars.av && svars.av[0])
            {
                if (*check_builtins(&svars) == NULL)
                {
                    search_path(&svars);
                }
            }
            free(svars.av);
        }

        free(svars.buffer);
        free(svars.commands);
        ctrl_c_flag = 0;

        if (is_pipe == 0)
        {
            _puts("($) "); /* Print shell prompt */
        }
        svars.buffer = NULL;
    } while (getline(&(svars.buffer), &buf_size, stdin) != -1);

    if (is_pipe == 0)
        _puts("\n"); /* Print a newline if not from a pipe */

    free_environment(svars.env); /* Clean up environment variables */
    free(svars.buffer);
    exit(svars.status); /* Exit with the status of the last command */
}
