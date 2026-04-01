/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:00:00 by lucas             #+#    #+#             */
/*   Updated: 2026/03/24 12:00:00 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// variable globale autorisee par le sujet.
// Elle stocke le numero du dernier signal recu.
// On l'utilise pour savoir si ctrl-C a ete presse
// et mettre a jour $? (exit status = 130 apres ctrl-C).
volatile sig_atomic_t	g_signal = 0;

// Handler appele quand ctrl-C (SIGINT) est presse en mode interactif
// (= quand le shell attend une commande dans readline).
//
// Ce qu'il fait :
// 1. Stocke le signal dans g_signal
// 2. printf("\n") → saute une ligne apres le ^C
// 3. rl_on_new_line() → dit a readline qu'on est sur une nouvelle ligne
// 4. rl_redisplay() → reaffiche le prompt
//
// Resultat : ctrl-C affiche un nouveau prompt propre, comme bash.
//
// Note : rl_replace_line() n'est pas dispo partout.
// write + rl_on_new_line + rl_redisplay suffit.
static void	handle_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// Mode interactif : quand le shell attend une commande.
//
// ctrl-C (SIGINT)  → handle_sigint (nouveau prompt)
// ctrl-\ (SIGQUIT) → SIG_IGN = ignore completement
//
// ctrl-D n'est PAS un signal, c'est un EOF.
// readline() retourne NULL quand ctrl-D est presse.
// C'est gere dans la boucle principale (minishell.c).
void	setup_signals_interactive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	if (isatty(STDIN_FILENO))
	{
		sa_int.sa_handler = handle_sigint;
		sa_int.sa_flags = 0;
		sigemptyset(&sa_int.sa_mask);
		sigaction(SIGINT, &sa_int, NULL);
		sa_quit.sa_handler = SIG_IGN;
		sa_quit.sa_flags = 0;
		sigemptyset(&sa_quit.sa_mask);
		sigaction(SIGQUIT, &sa_quit, NULL);
	}
	else
	setup_signals_default();
}


// Pour l'exec : quand une commande tourne dans un fork.
// On remet les signaux par defaut (SIG_DFL) pour que :
// ctrl-C → tue le processus enfant (comportement normal)
// ctrl-\ → tue le processus enfant + core dump (comportement normal)
//
// Le shell parent doit ignorer ces signaux pendant l'exec
// pour ne pas se tuer lui-meme.
void	setup_signals_default(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

// Mode parent pendant exec : le shell ignore les signaux
// pendant qu'un enfant tourne, pour ne pas se quitter.
// Apres le waitpid, ton binome devra rappeler
// setup_signals_interactive() pour revenir en mode normal.
void	setup_signals_ignore(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
