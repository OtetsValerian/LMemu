#include <gtk/gtk.h> /* подключаем GTK+ */

/* эта функци€ будет выполнена первой */
int main(int argc, char* argv[])
{
    /* тут мы объ€вим переменные */

    /* запускаем GTK+ */
    gtk_init(&argc, &argv);

    /* тут будет код нашего приложени€ */

    /* передаЄм управление GTK+ */
    gtk_main();

    return 0;
}