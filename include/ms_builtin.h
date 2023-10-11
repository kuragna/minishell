#ifndef MS_BUILTIN_H
#define MS_BUILTIN_H

#define SINGLE_QUOTE '\''
#define DOUBLE_QUOTE '\"'

void	ms_echo(char *str);
int		ms_pwd(void);
// void	ms_env(void);
int		ms_cd(const char *path);
// void	ms_unset(void);
// void	ms_export(void);

// void	ms_env(t_list *env);

#endif //MS_BUILTIN_H
