export module graal.packet.types;

export import graal.packet.types.client;
export import graal.packet.types.server;


export namespace graal::packet
{

enum class ClientPacket
{
	LEVELWARP = 0,
	BOARDMODIFY = 1,
	PLAYERPROPS = 2,
	NPCPROPS = 3,
	BOMBADD = 4,
	BOMBDEL = 5,
	TOALL = 6,
	HORSEADD = 7,
	HORSEDEL = 8,
	ARROWADD = 9,
	FIRESPY = 10,
	THROWCARRIED = 11,
	ITEMADD = 12,
	ITEMDEL = 13,
	CLAIMPKER = 14,
	BADDYPROPS = 15,
	BADDYHURT = 16,
	BADDYADD = 17,
	FLAGSET = 18,
	FLAGDEL = 19,
	OPENCHEST = 20,
	PUTNPC = 21,
	NPCDEL = 22,
	WANTFILE = 23,
	SHOWIMG = 24,
	UNKNOWN25 = 25,
	HURTPLAYER = 26,
	EXPLOSION = 27,
	PRIVATEMESSAGE = 28,
	NPCWEAPONDEL = 29,
	LEVELWARPMOD = 30,
	PACKETCOUNT = 31,
	ITEMTAKE = 32,
	WEAPONADD = 33,
	UPDATEFILE = 34,
	ADJACENTLEVEL = 35,
	HITOBJECTS = 36,
	LANGUAGE = 37,
	TRIGGERACTION = 38,
	MAPINFO = 39,
	SHOOT = 40,
	SERVERWARP = 41,
	PROCESSLIST = 44,
	UNKNOWN46 = 46,	// Always is 1.  Might be a player count for the gmap level.
	UNKNOWN47 = 47,	// Seems to tell the server the modTime of update files.  Used for client updates.
	RAWDATA = 50,
	RC_SERVEROPTIONSGET = 51,
	RC_SERVEROPTIONSSET = 52,
	RC_FOLDERCONFIGGET = 53,
	RC_FOLDERCONFIGSET = 54,
	RC_RESPAWNSET = 55,
	RC_HORSELIFESET = 56,
	RC_APINCREMENTSET = 57,
	RC_BADDYRESPAWNSET = 58,
	RC_PLAYERPROPSGET = 59,
	RC_PLAYERPROPSSET = 60,
	RC_DISCONNECTPLAYER = 61,
	RC_UPDATELEVELS = 62,
	RC_ADMINMESSAGE = 63,
	RC_PRIVADMINMESSAGE = 64,
	RC_LISTRCS = 65,
	RC_DISCONNECTRC = 66,
	RC_APPLYREASON = 67,
	RC_SERVERFLAGSGET = 68,
	RC_SERVERFLAGSSET = 69,
	RC_ACCOUNTADD = 70,
	RC_ACCOUNTDEL = 71,
	RC_ACCOUNTLISTGET = 72,
	RC_PLAYERPROPSGET2 = 73,	// Gets by player ID
	RC_PLAYERPROPSGET3 = 74,	// Gets by player account name.
	RC_PLAYERPROPSRESET = 75,
	RC_PLAYERPROPSSET2 = 76,
	RC_ACCOUNTGET = 77,
	RC_ACCOUNTSET = 78,
	RC_CHAT = 79,
	PROFILEGET = 80,
	PROFILESET = 81,
	RC_WARPPLAYER = 82,
	RC_PLAYERRIGHTSGET = 83,
	RC_PLAYERRIGHTSSET = 84,
	RC_PLAYERCOMMENTSGET = 85,
	RC_PLAYERCOMMENTSSET = 86,
	RC_PLAYERBANGET = 87,
	RC_PLAYERBANSET = 88,
	RC_FILEBROWSER_START = 89,
	RC_FILEBROWSER_CD = 90,
	RC_FILEBROWSER_END = 91,
	RC_FILEBROWSER_DOWN = 92,
	RC_FILEBROWSER_UP = 93,
	NPCSERVERQUERY = 94,
	RC_FILEBROWSER_MOVE = 96,
	RC_FILEBROWSER_DELETE = 97,
	RC_FILEBROWSER_RENAME = 98,
	NC_NPCGET = 103,	// {103}{INT id}
	NC_NPCDELETE = 104,	// {104}{INT id}
	NC_NPCRESET = 105,	// {105}{INT id}
	NC_NPCSCRIPTGET = 106,	// {106}{INT id}
	NC_NPCWARP = 107,	// {107}{INT id}{CHAR x*2}{CHAR y*2}{level}
	NC_NPCFLAGSGET = 108,	// {108}{INT id}
	NC_NPCSCRIPTSET = 109,	// {109}{INT id}{GSTRING script}
	NC_NPCFLAGSSET = 110,	// {110}{INT id}{GSTRING flags}
	NC_NPCADD = 111,	// {111}{GSTRING info}  - (info) name,id,type,scripter,starting level,x,y
	NC_CLASSEDIT = 112,	// {112}{class}
	NC_CLASSADD = 113,	// {113}{CHAR name length}{name}{GSTRING script}
	NC_LOCALNPCSGET = 114,	// {114}{level}
	NC_WEAPONLISTGET = 115,	// {115}
	NC_WEAPONGET = 116,	// {116}{weapon}
	NC_WEAPONADD = 117,	// {117}{CHAR weapon length}{weapon}{CHAR image length}{image}{code}
	NC_WEAPONDELETE = 118,	// {118}{weapon}
	NC_CLASSDELETE = 119,	// {119}{class}
	NC_LEVELLISTGET = 150,	// {150}
	NC_LEVELLISTSET = 151,	// {151}{GSTRING levels}

	REQUESTTEXT = 152,	// Gets a value from the server.
	SENDTEXT = 154,	// Sets a value on the server.

	RC_LARGEFILESTART = 155,
	RC_LARGEFILEEND = 156,

	UNKNOWN157 = 157,	// Something to do with ganis.
	UPDATESCRIPT = 158,	// {158}{script} Requests a script from the server.
	RC_FOLDERDELETE = 160,
	UPDATECLASS = 161,	// {161}{INT5 modtime}{name} Class request.
	RC_UNKNOWN162 = 162,	// Blank packet, sent by RC3 beta.

	COUNT
};

enum class ServerPacket
{
	LEVELBOARD = 0,
	LEVELLINK = 1,
	BADDYPROPS = 2,
	NPCPROPS = 3,
	LEVELCHEST = 4,
	LEVELSIGN = 5,
	LEVELNAME = 6,
	BOARDMODIFY = 7,
	OTHERPLPROPS = 8,
	PLAYERPROPS = 9,
	ISLEADER = 10,
	BOMBADD = 11,
	BOMBDEL = 12,
	TOALL = 13,
	PLAYERWARP = 14,
	WARPFAILED = 15,
	DISCMESSAGE = 16,
	HORSEADD = 17,
	HORSEDEL = 18,
	ARROWADD = 19,
	FIRESPY = 20,
	THROWCARRIED = 21,
	ITEMADD = 22,
	ITEMDEL = 23,
	NPCMOVED = 24,	// What does this do? Joey: Apparently just hides the npc ... for level warps??
	SIGNATURE = 25,
	NPCACTION = 26,	// What does this do?  Codr note: Unhandled by 6.037.
	BADDYHURT = 27,
	FLAGSET = 28,
	NPCDEL = 29,
	FILESENDFAILED = 30,
	FLAGDEL = 31,
	SHOWIMG = 32,
	NPCWEAPONADD = 33,
	NPCWEAPONDEL = 34,
	RC_ADMINMESSAGE = 35,
	EXPLOSION = 36,
	PRIVATEMESSAGE = 37,
	PUSHAWAY = 38,	// What does this do?
	LEVELMODTIME = 39,
	HURTPLAYER = 40,
	STARTMESSAGE = 41,	// Unhandled by 6.037. -Codr
	NEWWORLDTIME = 42,
	DEFAULTWEAPON = 43,
	HASNPCSERVER = 44,	// If sent, the client won't update npc props.  Codr note: Unhandled by 5.07+.
	FILEUPTODATE = 45,
	HITOBJECTS = 46,
	STAFFGUILDS = 47,
	TRIGGERACTION = 48,
	PLAYERWARP2 = 49,	// Bytes 1-3 are x/y/z. 4 = level x in gmap, 5 = level y in gmap.
	RC_ACCOUNTADD = 50,	// Deprecated.  Codr note: Unhandled by 6.037.
	RC_ACCOUNTSTATUS = 51,	// Deprecated.  Codr note: Unhandled by 6.037.
	RC_ACCOUNTNAME = 52,	// Deprecated.  Codr note: Unhandled by 6.037.
	RC_ACCOUNTDEL = 53,	// Deprecated.  Codr note: Unhandled by 6.037.
	RC_ACCOUNTPROPS = 54,	// Deprecated.  Codr note: Unhandled by 6.037.
	ADDPLAYER = 55,	// Unhandled by 5.07+. -Codr
	DELPLAYER = 56,	// Unhandled by 5.07+. -Codr
	RC_ACCOUNTPROPSGET = 57,	// Deprecated.  Codr note: Unhandled by 6.037.
	RC_ACCOUNTCHANGE = 58,	// Deprecated.  Codr note: Unhandled by 6.037.
	RC_PLAYERPROPSCHANGE = 59,	// Deprecated.  Codr note: Unhandled by 6.037.
	UNKNOWN60 = 60,	// Unhandled by 5.07+. -Codr
	RC_SERVERFLAGSGET = 61,	// Unhandled by 5.07+. -Codr
	RC_PLAYERRIGHTSGET = 62,	// Unhandled by 5.07+. -Codr
	RC_PLAYERCOMMENTSGET = 63,	// Unhandled by 5.07+. -Codr
	RC_PLAYERBANGET = 64,	// Unhandled by 5.07+. -Codr
	RC_FILEBROWSER_DIRLIST = 65,	// Unhandled by 5.07+. -Codr
	RC_FILEBROWSER_DIR = 66,	// Unhandled by 5.07+. -Codr
	RC_FILEBROWSER_MESSAGE = 67,
	LARGEFILESTART = 68,
	LARGEFILEEND = 69,
	RC_ACCOUNTLISTGET = 70,	// Unhandled by 5.07+. -Codr
	RC_PLAYERPROPS = 71,	// Deprecated.  Codr note: Unhandled by 6.037.
	RC_PLAYERPROPSGET = 72,	// Unhandled by 5.07+. -Codr
	RC_ACCOUNTGET = 73,	// Unhandled by 5.07+. -Codr
	RC_CHAT = 74,
	PROFILE = 75,	// Unhandled by 6.037. -Codr
	RC_SERVEROPTIONSGET = 76,	// Unhandled by 5.07+. -Codr
	RC_FOLDERCONFIGGET = 77,	// Unhandled by 5.07+. -Codr
	NC_CONTROL = 78,	// HIJACKED BY GR!  No clue as to its official purpose.  Codr note: Unhandled by 5.07+.
	NPCSERVERADDR = 79,	// Bytes 1-2 are 0 and 2, followed by a string formatted as <ipaddr>,<port>.  Codr note: Unhandled by 5.07+.
	NC_LEVELLIST = 80,	// {80}{GSTRING levels}  Codr note: Unhandled by 5.07+.
	UNKNOWN81 = 81,	// Unhandled by 5.07+. -Codr
	SERVERTEXT = 82,	// Answer to PLI_REQUESTTEXT and PLI_SENDTEXT.
	UNKNOWN83 = 83,	// Unhandled by 5.07+. -Codr
	LARGEFILESIZE = 84,
	RAWDATA = 100,	// {100}{INT3 length}  Codr note: Unhandled by 5.07+.
	BOARDPACKET = 101,
	FILE = 102,
	RC_MAXUPLOADFILESIZE = 103,	// {GINT5} - Upload file size limit in bytes. Default to 20 mebibytes
	UNKNOWN104 = 104,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	UNKNOWN105 = 105,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	UNKNOWN106 = 106,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	UNKNOWN107 = 107,	// Basically PLO_LEVELBOARD for extra level layers.
	UNKNOWN109 = 109,	// Valid message in 6.037. -Codr
	UNKNOWN111 = 111,	// Valid message in 6.037. -Codr
	UNKNOWN124 = 124,	// 5/26/2019: RC3 receives this, only hint I seen was regarding receiving player flags? Didn't try to test it though 
	NPCBYTECODE = 131,	// Compiled Torque-script for an NPC. {131}{INT3 id}{code}
	UNKNOWN132 = 132,	// Valid message in 5.07.  The code it uses is unique.  Unhandled by 6.037. -Codr
	UNKNOWN133 = 133,	// Valid message in 5.07.  The code it uses is unique.  Unhandled by 6.037. -Codr
	UNKNOWN134 = 134,	// Might be used for package downloads.
	NPCWEAPONSCRIPT = 140,	// {140}{INT2 info_length}{script}
	NPCDEL2 = 150,	// {150}{CHAR level_length}{level}{INT3 npcid}
	HIDENPCS = 151,
	SAY2 = 153,	// Also used for signs. {153}{text}
	FREEZEPLAYER2 = 154,	// Blank.
	UNFREEZEPLAYER = 155,	// Blank.
	SETACTIVELEVEL = 156,	// Sets the level to receive chests, baddies, NPCs, etc.
	NC_NPCATTRIBUTES = 157,	// {157}{GSTRING attributes}  Codr note: Unhandled by 5.07+.
	NC_NPCADD = 158,	// {158}{INT id}{CHAR 50}{CHAR name length}{name}{CHAR 51}{CHAR type length}{type}{CHAR 52}{CHAR level length}{level}  Codr note: Unhandled by 5.07+.
	NC_NPCDELETE = 159,	// {159}{INT id}  Codr note: Unhandled by 5.07+.
	NC_NPCSCRIPT = 160,	// {160}{INT id}{GSTRING script}  Codr note: Unhandled by 5.07+.
	NC_NPCFLAGS = 161,	// {161}{INT id}{GSTRING flags}  Codr note: Unhandled by 5.07+.
	NC_CLASSGET = 162,	// {162}{CHAR name length}{name}{GSTRING script}  Codr note: Unhandled by 5.07+.
	NC_CLASSADD = 163,	// {163}{class}  Codr note: Unhandled by 5.07+.
	NC_LEVELDUMP = 164,	// Unhandled by 5.07+. -Codr
	MOVE = 165,	// Unhandled by 6.037. -Codr
	UNKNOWN166 = 166,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	NC_WEAPONLISTGET = 167,	// {167}{CHAR name1 length}{name1}{CHAR name2 length}{name2}...  Codr note: Unhandled by 5.07+.
	UNKNOWN168 = 168,	// Login server sends this.  Blank packet.
	UNKNOWN169 = 169,	// Valid message in 5.07.  It's strange... the parameter seems to be a direct pointer value which would be difficult for the server to know about unless the client actually sends that information.  I don't know what purpose that could serve, however.  Unhandled by 6.037. -Codr
	GHOSTMODE = 170,
	BIGMAP = 171,	// Unhandled by 6.037. -Codr
	MINIMAP = 172,	// [172] zodiacminimap.txt,zodiacworldminimap3.png,10,10
	GHOSTTEXT = 173,	// {173}{text}  Shows static text in lower-right corner of screen only when in ghost mode.
	GHOSTICON = 174,	// Pass 1 to enable the ghost icon
	SHOOT = 175,	// Unhandled by 6.037. -Codr
	FULLSTOP = 176,	// Sending this causes the entire client to not respond to normal input and it hides the HUD.
	FULLSTOP2 = 177,	// Sending this causes the entire client to not respond to normal input and it hides the HUD.  Codr note: Unhandled by 5.07+.
	SERVERWARP = 178,
	RPGWINDOW = 179,
	STATUSLIST = 180,
	UNKNOWN181 = 181,	// Valid message in 5.07.  The code it uses is unique.  Unhandled by 6.037. -Codr
	LISTPROCESSES = 182,
	UNKNOWN183 = 183,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	UNKNOWN184 = 184,	// Valid message in 5.07.  The code it uses is unique.  The string "screenshots" is present in the code.  I didn't look in detail.  Unhandled by 6.037. -Codr
	UNKNOWN185 = 185,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	UNKNOWN186 = 186,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	UNKNOWN187 = 187,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	NC_CLASSDELETE = 188,	// {188}{class}  Codr note: Unhandled by 5.07+.
	MOVE2 = 189,	// {189}{INT id}...
	UNKNOWN190 = 190,	// Was blank.  Sent before weapon list. NOTE: Sending this packet makes the client login to irc, request bantypes, pmguilds, pmservers, globalpms, buddytracking and stuff... Mainly tied to setTex
	UNKNOWN191 = 191,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	NC_WEAPONGET = 192,	// {192}{CHAR name length}{name}{CHAR image length}{image}{script}  Codr note: Unhandled by 5.07+.
	UNKNOWN193 = 193,	// Valid message in 5.07.  The code it uses is unique.  The first parameter is likely a 5-byte integer.  There may be more.  Unhandled by 6.037. -Codr
	UNKNOWN194 = 194,	// Was blank.  Sent before weapon list.
	UNKNOWN195 = 195,	// Something to do with ganis.  [195] )twiz-icon"SETBACKTO "

	// Seems to register NPCs or something on the client.
	// Also is related to PLI_UPDATESCRIPT as it sends the last modification time of the NPC/weapon.  The v5 client stores weapon scripts offline.
	UNKNOWN197 = 197,	// Seems to register npcs on the client.  Also is used by client to see if it needs to get a newer version of the offline cache of the NPC.
	UNKNOWN198 = 198,	// Valid message in 6.037. -Codr

	COUNT
};

} // end namespace graal::packets
