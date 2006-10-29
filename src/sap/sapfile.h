/*
 * SAP xmms plug-in. 
 * Copyright 2002/2003 by Michal 'Mikey' Szwaczko <mikey@scene.pl>
 *
 * SAP Library ver. 1.56 by Adam Bienias
 *
 * This is free software. You can modify it and distribute it under the terms
 * of the GNU General Public License. The verbatim text of the license can 
 * be found in file named COPYING in the source directory.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

char buffer[0x10000]; 

char author[2048];
char name[2048];
char date[2048];
char type[20]; /* type in ascii */
char type_h; /* type as seen in SAP header; */

long filesize;

int headersize;    
int is_stereo;
int fastplay;
int plr_address;
int msx_address;
int ini_address;
int songs;
int defsong; 
int times_per_frame; /* times per frame */
