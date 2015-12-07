#if 1
if (n == num_philosophers - 1)
    for (;;)
      {
	/* The last philosopher is different.  He goes for his right
	   fork first, so there is no cycle in the mutex graph.  */

	/* Grab the right fork.  */
	pthread_mutex_lock (&fork_mutex[(n + 1) % num_philosophers]);
	print_philosopher (n, '_', '!');
	random_delay ();

	/* Then grab the left fork. */
	pthread_mutex_lock (&fork_mutex[n]);
	print_philosopher (n, '!', '!');
	random_delay ();

	print_philosopher (n, '_', '_');
	pthread_mutex_unlock (&fork_mutex[n]);
	pthread_mutex_unlock (&fork_mutex[(n + 1) % num_philosophers]);
	random_delay ();
      }
  else
#endif
    for (;;)
      {
	/* Grab the left fork. */
	pthread_mutex_lock (&fork_mutex[n]);
	print_philosopher (n, '!', '_');
	random_delay ();

	/* Then grab the right fork.  */
	pthread_mutex_lock (&fork_mutex[(n + 1) % num_philosophers]);
	print_philosopher (n, '!', '!');
	random_delay ();

	print_philosopher (n, '_', '_');
	pthread_mutex_unlock (&fork_mutex[n]);
	pthread_mutex_unlock (&fork_mutex[(n + 1) % num_philosophers]);
	random_delay ();
      }
