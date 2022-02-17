#ifndef APP_H
#define APP_H

typedef struct {
	const char *title;
	int width;
	int height;
	int gl_major_version;
	int gl_minor_version;
} AppInfo;

typedef struct App App;

App *App_make(const AppInfo *app_info);
void App_free(App *app);

void App_run(const App *app, void (*init_func)(void), void (*loop_func)(void));

#endif