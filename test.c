

int	ft_lock_right_fork(t_philosopher *p)
{
    int loop_control = 1;

    pthread_mutex_lock(&p->resources->print_console_mtx);
    while (loop_control == 1 && p->resources->simulation_ended == 0)
    {
        pthread_mutex_unlock(&p->resources->print_console_mtx);

        pthread_mutex_lock(&p->resources->forks_mtxs[p->id]);
        if (p->resources->forks[p->id] == AVAILABLE)
        {
            p->resources->forks[p->id] = TAKEN;
            p->right_fork = HOLD;

            // Print status
            pthread_mutex_lock(&p->resources->print_console_mtx);
            if (p->resources->simulation_ended == 0) // Ensure simulation_ended is properly checked
                ft_print_fork_status(p, RIGHT_FORK);
            pthread_mutex_unlock(&p->resources->print_console_mtx);

            pthread_mutex_unlock(&p->resources->forks_mtxs[p->id]);
            loop_control = 0;
        }
        else
        {
            pthread_mutex_unlock(&p->resources->forks_mtxs[p->id]);
        }

        // Check the condition again before re-entering the loop
        pthread_mutex_lock(&p->resources->print_console_mtx);
    }
    pthread_mutex_unlock(&p->resources->print_console_mtx);
    return (0);
}
