#ifndef MS_BUILTIN_H
#define MS_BUILTIN_H


// NOTE: after all let's declare string literaly as const
void	ms_echo(char *str);
int		ms_pwd(void);
void	ms_env(void);
void	ms_cd(void);
void	ms_unset(void);
void	ms_export(void);

#endif //MS_BUILTIN_H
