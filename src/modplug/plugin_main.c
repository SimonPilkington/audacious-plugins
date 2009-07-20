#include <audacious/plugin.h>

void Init(void);
void ShowAboutBox(void);
void ShowConfigureBox(void);
void PlayFile(InputPlayback *data);
void Stop(InputPlayback *data);
void Pause(InputPlayback *data, gshort aPaused);
void Seek(InputPlayback *data, gint aTime);
gint GetTime(InputPlayback *data);
void ShowFileInfoBox(char* aFilename);
Tuple* GetSongTuple(const gchar* aFilename);
gint CanPlayFileFromVFS(const gchar* aFilename, VFSFile *VFSFile);

static const gchar *fmts[] =
    { "amf", "ams", "dbm", "dbf", "dsm", "far", "mdl", "stm", "ult", "mt2",
      "mdz", "mdr", "mdgz", "mdbz", "mod", "s3z", "s3r", "s3gz", "s3m", "xmz", "xmr", "xmgz",
      "itz", "itr", "itgz", "dmf", "umx", "it", "669", "xm", "mtm", "psm", "ft2",
      "zip", "gz", "bz2", "rar", "rb",
      NULL };

InputPlugin gModPlug =
{
    .description = "ModPlug Audio Plugin",
    .init = Init,
    .about = ShowAboutBox,
    .configure = ShowConfigureBox,
    .enabled = FALSE,
    .play_file = PlayFile,
    .stop = Stop,
    .pause = Pause,
    .seek = Seek,
    .get_time = GetTime,
    .file_info_box = ShowFileInfoBox,
    .get_song_tuple = GetSongTuple,
    .is_our_file_from_vfs = CanPlayFileFromVFS,
    .vfs_extensions = (gchar **)fmts,
    .have_subtune = TRUE,   // to exclude .zip etc which doesn't contain any mod file --yaz
};

InputPlugin *modplug_iplist[] = { &gModPlug, NULL };

SIMPLE_INPUT_PLUGIN(modplug, modplug_iplist);
