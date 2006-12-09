#include "settings.h"

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "audacious/util.h"
#include "audacious/configdb.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "md5.h"

#include <glib.h>
#include <glib/gi18n.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "configure.h"

GtkWidget *entry1, *entry2, *ge_entry1, *ge_entry2, *cfgdlg;

static char *hexify(char *pass, int len)
{
        static char buf[33];
        char *bp = buf;
        char hexchars[] = "0123456789abcdef";
        int i;

        memset(buf, 0, sizeof(buf));

        for(i = 0; i < len; i++) {
                *(bp++) = hexchars[(pass[i] >> 4) & 0x0f];
                *(bp++) = hexchars[pass[i] & 0x0f];
        }
        *bp = 0;
        return buf;
}

static void saveconfig(GtkWidget *wid __attribute__((unused)), gpointer data)
{
        ConfigDb *cfgfile;

        const char *uid = gtk_entry_get_text(GTK_ENTRY(entry1));
        const char *pwd = gtk_entry_get_text(GTK_ENTRY(entry2));
        const char *ge_uid = gtk_entry_get_text(GTK_ENTRY(ge_entry1));
        const char *ge_pwd = gtk_entry_get_text(GTK_ENTRY(ge_entry2));

        if ((cfgfile = bmp_cfg_db_open()))
	{
                md5_state_t md5state;
                unsigned char md5pword[16], ge_md5pword[16];

                bmp_cfg_db_set_string(cfgfile, "audioscrobbler", "username", (char *)uid);
                bmp_cfg_db_set_string(cfgfile, "audioscrobbler", "ge_username", (char *)ge_uid);

                if (pwd != NULL && pwd[0] != '\0')
		{
                        md5_init(&md5state);
                        md5_append(&md5state, (unsigned const char *)pwd, strlen(pwd));
                        md5_finish(&md5state, md5pword);
                        bmp_cfg_db_set_string(cfgfile, "audioscrobbler", "password",
                                        hexify((char*)md5pword, sizeof(md5pword)));
                }

                if (ge_pwd != NULL && ge_pwd[0] != '\0')
		{
                        md5_init(&md5state);
                        md5_append(&md5state, (unsigned const char *)ge_pwd, strlen(ge_pwd));
                        md5_finish(&md5state, ge_md5pword);
                        bmp_cfg_db_set_string(cfgfile, "audioscrobbler", "ge_password",
                                        hexify((char*)ge_md5pword, sizeof(ge_md5pword)));
                }

                bmp_cfg_db_close(cfgfile);
        }
}

/* Generated by glade, sorta. */
GtkWidget *
create_cfgdlg(void)
{
  ConfigDb *db;
  GtkWidget *vbox2;
  GtkWidget *table1;
  GtkWidget *label3;
  GtkWidget *label1;
  GtkWidget *label2;
  GtkWidget *himage1;
  GtkWidget *align1;
  GtkWidget *notebook1;

  vbox2 = gtk_vbox_new (FALSE, 0);

  label1 = gtk_label_new (_("<b>Services</b>"));
  gtk_widget_show (label1);
  gtk_label_set_use_markup (GTK_LABEL (label1), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label1), 0, 0.5);

  gtk_box_pack_start (GTK_BOX (vbox2), label1, FALSE, FALSE, 0);

  notebook1 = gtk_notebook_new();
  gtk_widget_show (notebook1);

  align1 = gtk_alignment_new(0, 0, 0, 0);
  gtk_widget_show (align1);
  gtk_alignment_set_padding(GTK_ALIGNMENT(align1), 0, 0, 12, 0);

  table1 = gtk_table_new (2, 2, FALSE);
  gtk_widget_show (table1);
  gtk_container_add(GTK_CONTAINER(align1), table1);
  gtk_table_set_row_spacings (GTK_TABLE(table1), 6);
  gtk_table_set_col_spacings (GTK_TABLE(table1), 6);

  label2 = gtk_label_new (_("Username:"));
  gtk_widget_show (label2);
  gtk_table_attach_defaults (GTK_TABLE (table1), label2, 0, 1, 2, 3);
  gtk_label_set_justify (GTK_LABEL (label2), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (label2), 1, 0.5);

  label3 = gtk_label_new (_("Password:"));
  gtk_widget_show (label3);
  gtk_table_attach (GTK_TABLE (table1), label3, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_justify (GTK_LABEL (label3), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (label3), 1, 0.5);

  entry1 = gtk_entry_new ();
  gtk_widget_show (entry1);
  gtk_table_attach_defaults (GTK_TABLE (table1), entry1, 1, 2, 2, 3);

  entry2 = gtk_entry_new ();
  gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);
  gtk_widget_show (entry2);
  gtk_table_attach_defaults (GTK_TABLE (table1), entry2, 1, 2, 3, 4);
  g_signal_connect(entry2, "changed", (GCallback) saveconfig, NULL);

  label1 = gtk_label_new (_("<b>Last.FM</b>"));
  gtk_label_set_use_markup (GTK_LABEL (label1), TRUE);
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), GTK_WIDGET(align1), label1);

  align1 = gtk_alignment_new(0, 0, 0, 0);
  gtk_widget_show (align1);
  gtk_alignment_set_padding(GTK_ALIGNMENT(align1), 0, 0, 12, 0);

  table1 = gtk_table_new (2, 2, FALSE);
  gtk_widget_show (table1);
  gtk_container_add(GTK_CONTAINER(align1), table1);
  gtk_table_set_row_spacings (GTK_TABLE(table1), 6);
  gtk_table_set_col_spacings (GTK_TABLE(table1), 6);

  label2 = gtk_label_new (_("Username:"));
  gtk_widget_show (label2);
  gtk_table_attach_defaults (GTK_TABLE (table1), label2, 0, 1, 2, 3);
  gtk_label_set_justify (GTK_LABEL (label2), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (label2), 1, 0.5);

  label3 = gtk_label_new (_("Password:"));
  gtk_widget_show (label3);
  gtk_table_attach (GTK_TABLE (table1), label3, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_justify (GTK_LABEL (label3), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (label3), 1, 0.5);

  ge_entry1 = gtk_entry_new ();
  gtk_widget_show (ge_entry1);
  gtk_table_attach_defaults (GTK_TABLE (table1), ge_entry1, 1, 2, 2, 3);

  ge_entry2 = gtk_entry_new ();
  gtk_entry_set_visibility(GTK_ENTRY(ge_entry2), FALSE);
  gtk_widget_show (ge_entry2);
  gtk_table_attach_defaults (GTK_TABLE (table1), ge_entry2, 1, 2, 3, 4);
  g_signal_connect(ge_entry2, "changed", (GCallback) saveconfig, NULL);

  label1 = gtk_label_new (_("<b>Gerpok</b>"));
  gtk_label_set_use_markup (GTK_LABEL (label1), TRUE);
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), GTK_WIDGET(align1), label1);

  gtk_box_pack_start (GTK_BOX (vbox2), notebook1, TRUE, TRUE, 6);

  himage1 = gtk_image_new_from_file (DATA_DIR "/images/audioscrobbler_badge.png");
  gtk_widget_show (himage1);
  gtk_box_pack_start (GTK_BOX (vbox2), himage1, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (himage1), 1, 0.5);

	gtk_entry_set_text(GTK_ENTRY(entry1), "");
	gtk_entry_set_text(GTK_ENTRY(entry2), "");

        if ((db = bmp_cfg_db_open())) {
                gchar *username = NULL;
                bmp_cfg_db_get_string(db, "audioscrobbler", "username",
                        &username);
                if (username) {
                        gtk_entry_set_text(GTK_ENTRY(entry1), username);
                        g_free(username);
			username = NULL;
                }
                bmp_cfg_db_get_string(db, "audioscrobbler", "ge_username",
                        &username);
                if (username) {
                        gtk_entry_set_text(GTK_ENTRY(ge_entry1), username);
                        g_free(username);
                }
                bmp_cfg_db_close(db);
        }

  return vbox2;
}

