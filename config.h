/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "firefox"
#define FILEMANAGER "pcmanfm"

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 20;       /* horiz inner gap between windows */
static unsigned int gappiv    = 10;       /* vert inner gap between windows */
static unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char *fonts[]          = { "Iosevka Comfy:size=12:antialias=true:autohint=true:style=SemiBold", "FontAwesome:size=16:antialias=true:autohint=true"};
static char normbgcolor[]	   = "#292031";
static char normbordercolor[]       = "#444444";
// static char normfgcolor[]           = "#bbbbbb";
static char normfgcolor[]           = "#999999";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#000077";
// static char selbgcolor[]            = "#524e37";
static char selbgcolor[]            = "#483752";

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
// const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-g", "60x20", "-e", "qalc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const char *tags[] = { "", "2", "3", "4", "5", "6", "7", "8", "9", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     		NULL,       NULL,       	1 << 8,     0,           0,         0,        -1 },
	{ TERMCLASS,  		NULL,       NULL,       	0,          0,           1,         0,        -1 },
	{ NULL,       		NULL,       "Event Tester",	0,          0,           0,         1,        -1 },
	{ TERMCLASS,     	"floatterm",NULL,       	0,			1,           1,         0,        -1 },
	{ TERMCLASS,     	"bg",       NULL,       	1 << 7,     0,           1,         0,        -1 },
	{ TERMCLASS,     	"spterm",   NULL,       	SPTAG(0),   1,           1,         0,        -1 },
	{ TERMCLASS,    	"spcalc", 	NULL,       	SPTAG(1),   1,           1,         0,        -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */

	// { "",	tile },			/* Default: Master on left, slaves on right */
	// { "",	tile },			/* Default: Master on left, slaves on right */
	// { "",	tile },			/* Default: Master on left, slaves on right */

	{ "",	tile },			/* Default: Master on left, slaves on right */

	// { "",	bstack },		/* Master on top, slaves on bottom */
	{ "",	bstack },		/* Master on top, slaves on bottom */

	{ "",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "",	deck },			/* Master on left, slaves in monocle-like mode on right */

	// { "",	monocle },		/* All windows on top of eachother */
	{ "",	monocle },		/* All windows on top of eachother */

	// { "[]",	centeredmaster },		/* Master in middle, slaves on sides */
	{ "[]",	centeredmaster },		/* Master in middle, slaves on sides */

	// { ">M>",	centeredfloatingmaster },	/* Same but master floats */
	{ "",		centeredfloatingmaster },	/* Same but master floats */

	// { "",	NULL },			/* no layout function means floating behavior */
	{ "",		NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },		/* null-terminate layout symbol and name*/
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_Right,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_Left,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	// { MOD, XK_masculine, ACTION##stack, {.i = PREVSEL } }, \
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	/* { MODKEY|ShiftMask,		XK_Escape,	spawn,	SHCMD("") }, */
	// { MODKEY,			XK_grave,	spawn,	{.v = (const char*[]){ "dmenuunicode", NULL } } },
	/* { MODKEY|ShiftMask,		XK_grave,	togglescratch,	SHCMD("") }, */
	TAGKEYS(				XK_1,		0)
	TAGKEYS(				XK_2,		1)
	TAGKEYS(				XK_3,		2)
	TAGKEYS(				XK_4,		3)
	TAGKEYS(				XK_5,		4)
	TAGKEYS(				XK_6,		5)
	TAGKEYS(				XK_7,		6)
	TAGKEYS(				XK_8,		7)
	TAGKEYS(				XK_9,		8)
	/* Custom tags*/
	TAGKEYS(				XK_f,		9)
	TAGKEYS(				XK_b,		10)
	TAGKEYS(				XK_v,		11)
	// TAGKEYS(				XK_y,		11)
	// TAGKEYS(				XK_s,		12)
	{ MODKEY,				XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },

	// Reload DWM like i3wm. (Assuming there is a single DWM instance)
	
	// { MODKEY|ShiftMask,		XK_r,		spawn,		SHCMD("kill -HUP $(pgrep dwm)") },
	// { MODKEY|ShiftMask,		XK_r,		spawn,		SHCMD("kill -HUP $(pidof dwm)") },
	{ MODKEY|ShiftMask,		XK_r,		sighup},

	{ MODKEY|ShiftMask,		XK_e,		spawn,			{.v = (const char*[]){ "exit-dwm", NULL } } },

	{ MODKEY|ShiftMask,		XK_w,		spawn,		SHCMD("find ~/Pictures/Wallpapers -type f | shuf | sxiv - -t") },

	// Focus current media player
	{ MODKEY,		XK_p,		spawn,		SHCMD("dbus-send --type=method_call --dest=org.mpris.MediaPlayer2.playerctld /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Raise") },

	{ MODKEY,				XK_Tab,		view,		{0} },
	{ MODKEY,				XK_q,		killclient,	{0} },

	/* { MODKEY,				XK_b,		spawn,		{.v = (const char*[]){ BROWSER, NULL } } }, */
	/* { MODKEY,				XK_v,		spawn,		{.v = (const char*[]){ "kitty", "-e", "cava", NULL } } }, */
	/* { MODKEY,				XK_f,		spawn,		{.v = (const char*[]){ FILEMANAGER, NULL } } }, */

	/* In case you're sure you don't need more than one instance of each*/
	{ MODKEY,				XK_b,		spawn,		SHCMD("pgrep $BROWSER || $BROWSER") },
	{ MODKEY,				XK_f,		spawn,		SHCMD("pgrep pcmanfm || pcmanfm") },
	{ MODKEY,				XK_v,		spawn,		SHCMD("pgrep cava || kitty -e cava") },
	{ MODKEY,				XK_x,		spawn,		SHCMD("(pgrep xkill && pkill xkill) || xkill") },

	// { MODKEY,			XK_minus,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
	// { MODKEY,			XK_minus,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
	// { MODKEY|ShiftMask,		XK_minus,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)") },
	// { MODKEY,			XK_equal,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
	// { MODKEY|ShiftMask,		XK_equal,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)") },
	// { MODKEY,			XK_BackSpace,	spawn,		{.v = (const char*[]){ "sysact", NULL } } },
	// { MODKEY|ShiftMask,		XK_BackSpace,	spawn,		{.v = (const char*[]){ "sysact", NULL } } },

	/* { MODKEY|ShiftMask,		XK_Tab,		spawn,		SHCMD("") }, */
	// { MODKEY|ShiftMask,		XK_q,		spawn,		{.v = (const char*[]){ "sysact", NULL } } },
	// { MODKEY|ShiftMask,		XK_w,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "sudo", "nmtui", NULL } } },
	// { MODKEY,			XK_e,		spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook 2>/dev/null") },
	// { MODKEY|ShiftMask,		XK_e,		spawn,		SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") },
	// { MODKEY,			XK_r,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "lfub", NULL } } },
	// { MODKEY|ShiftMask,		XK_r,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },

	{ MODKEY|ShiftMask,		XK_t,		cycle_layout,	{0} }, /* bstack */

	// { MODKEY,				XK_t,		setlayout,	{.v = &layouts[0]} }, /* tile */
	// { MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} }, /* bstack */c
	// { MODKEY,				XK_y,		setlayout,	{.v = &layouts[2]} }, /* spiral */
	// { MODKEY|ShiftMask,		XK_y,		setlayout,	{.v = &layouts[3]} }, /* dwindle */
	// { MODKEY,				XK_u,		setlayout,	{.v = &layouts[4]} }, /* deck */
	// { MODKEY|ShiftMask,		XK_u,		setlayout,	{.v = &layouts[5]} }, /* monocle */
	// { MODKEY,				XK_i,		setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	// { MODKEY|ShiftMask,		XK_i,		setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,				XK_o,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,     {.i = -1 } },

	// { MODKEY,			XK_p,			spawn,		{.v = (const char*[]){ "mpc", "toggle", NULL } } },
	// { MODKEY|ShiftMask,		XK_p,			spawn,		SHCMD("mpc pause; pauseallmpv") },
	// { MODKEY,			XK_bracketleft,		spawn,		{.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	// { MODKEY|ShiftMask,		XK_bracketleft,		spawn,		{.v = (const char*[]){ "mpc", "seek", "-60", NULL } } },
	// { MODKEY,			XK_bracketright,	spawn,		{.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	// { MODKEY|ShiftMask,		XK_bracketright,	spawn,		{.v = (const char*[]){ "mpc", "seek", "+60", NULL } } },
	// { MODKEY,			XK_backslash,		view,		{0} },
	/* { MODKEY|ShiftMask,		XK_backslash,		spawn,		SHCMD("") }, */

	{ MODKEY,				XK_a,		togglegaps,	{0} },
	{ MODKEY|ShiftMask,		XK_a,		defaultgaps,	{0} },
	{ MODKEY,				XK_s,		togglesticky,	{0} },

	/* { MODKEY|ShiftMask,		XK_s,		spawn,		SHCMD("") }, */
	
	// { MODKEY|ShiftMask,		XK_s,		spawn,		SHCMD("area-screenshot") },
	// { MODKEY,				XK_d,		spawn,     	SHCMD( "dmenu_run -i -b -fn 'Dejavu Sans Book:size=11' -nb '#00001F' -nf '#FFFFFF' -sb '#FFFFFF' -sf '#000000'") },

	{ MODKEY|ShiftMask,		XK_s,		spawn,			{.v = (const char*[]){ "area-screenshot", NULL } } },
	{ MODKEY|ShiftMask,		XK_x,		spawn,			{.v = (const char*[]){ "dmenu-kill", NULL } } },
	{ MODKEY|ControlMask,	XK_s,		spawn,			{.v = (const char*[]){ "dmenu-search", NULL } } },

	{ MODKEY,				XK_d,		spawn,          {.v = (const char*[]){ 
	"dmenu_run",
	"-p",
	"Run which program? ❱",
	// "Run which program? ➔",
	// "-b", 
	"-fn",
	// "Dejavu Sans Book:size=11",
	"Iosevka Comfy:size=12:antialias=true:autohint=true:style=SemiBold",
	"-nb",
	// "#000055",
	// "#000000",
	"#00002F",
	"-nf",
	"#999999",
	"-sb",
	"#000055",
	// "#000000",
	// "#00002F",
	"-sf",
	"#FFFFFF",
	NULL } } },

	// F11 seems to be the de-facto standard for most GUI programs
	{ 0,					XK_F11,			togglefullscr,	{0} },
	{ MODKEY,				XK_F11,			togglebar,	{0} },
	{ MODKEY,				XK_t,			new_tag,	{0} },

	{ MODKEY|ShiftMask,		XK_f,			setlayout,	{.v = &layouts[8]} },
	{ MODKEY,				XK_g,			shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_g,			shifttag,	{ .i = -1 } },

	{ MODKEY,				XK_l,			setmfact,   {.f = +0.02} },
	{ MODKEY,				XK_h,			setmfact,	{.f = -0.02} },

	{ MODKEY,				XK_semicolon,	shiftview,	{ .i = 1 } },
	{ MODKEY|ShiftMask,		XK_semicolon,	shifttag,	{ .i = 1 } },

	{ MODKEY,				XK_apostrophe,	togglescratch,	{.ui = 0} },
	{ MODKEY,				XK_exclamdown,	togglescratch,	{.ui = 1} },

	{ MODKEY|ShiftMask,		XK_apostrophe,	togglesmartgaps,	{0} },
	{ MODKEY,				XK_Return,		spawn,		{.v = termcmd } },

	{ MODKEY,				XK_plus,		incrgaps,	{.i = +3 } },
	{ MODKEY,				XK_dead_grave,	incrgaps,	{.i = -3 } },
	
	// { MODKEY,			XK_c,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "profanity", NULL } } },
	/* { MODKEY|ShiftMask,		XK_c,		spawn,		SHCMD("") }, */
	/* V is automatically bound above in STACKKEYS */

	/* { MODKEY|ShiftMask,		XK_b,		spawn,		SHCMD("") }, */
	// { MODKEY,			XK_n,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "nvim", "-c", "VimwikiIndex", NULL } } },
	// { MODKEY|ShiftMask,		XK_n,		spawn,		SHCMD(TERMINAL " -e newsboat ; pkill -RTMIN+6 dwmblocks") },
	// { MODKEY,			XK_m,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	// { MODKEY|ShiftMask,		XK_m,		spawn,		SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	// { MODKEY,			XK_comma,	spawn,		{.v = (const char*[]){ "mpc", "prev", NULL } } },
	// { MODKEY|ShiftMask,		XK_comma,	spawn,		{.v = (const char*[]){ "mpc", "seek", "0%", NULL } } },
	// { MODKEY,			XK_period,	spawn,		{.v = (const char*[]){ "mpc", "next", NULL } } },
	// { MODKEY|ShiftMask,		XK_period,	spawn,		{.v = (const char*[]){ "mpc", "repeat", NULL } } },

	{ MODKEY,				XK_Left,		focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Left,		tagmon,		{.i = -1 } },
	{ MODKEY,				XK_Right,		focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Right,		tagmon,		{.i = +1 } },

	{ MODKEY,				XK_Page_Up,		shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_Page_Up,		shifttag,	{ .i = -1 } },
	{ MODKEY,				XK_Page_Down,	shiftview,	{ .i = +1 } },
	{ MODKEY|ShiftMask,		XK_Page_Down,	shifttag,	{ .i = +1 } },

	// { MODKEY,			XK_F4,		spawn,		SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	// { MODKEY,			XK_F5,		xrdb,		{.v = NULL } },
	// { MODKEY,			XK_F6,		spawn,		{.v = (const char*[]){ "torwrap", NULL } } },
	// { MODKEY,			XK_F7,		spawn,		{.v = (const char*[]){ "td-toggle", NULL } } },
	// { MODKEY,			XK_F8,		spawn,		{.v = (const char*[]){ "mailsync", NULL } } },
	// { MODKEY,			XK_F9,		spawn,		{.v = (const char*[]){ "mounter", NULL } } },
	// { MODKEY,			XK_F10,		spawn,		{.v = (const char*[]){ "unmounter", NULL } } },
	// { MODKEY,			XK_F11,		spawn,		SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	// { MODKEY,			XK_F12,		spawn,		SHCMD("remaps") },

	{ MODKEY|ShiftMask,		XK_space,	zoom,		{0} },
	{ MODKEY,				XK_space,	spawn,		{.v = (const char*[]){ "mpris-play-pause", NULL } } },
	{ MODKEY,				XK_minus,	spawn,		{.v = (const char*[]){ "notify-metadata", NULL } } },

	{ MODKEY,				XK_KP_Add,		spawn,	{.v = (const char*[]){ "change-volume", "-1", NULL } } },
	{ MODKEY,				XK_KP_Subtract,	spawn,	{.v = (const char*[]){ "change-volume", "+1", NULL } } },
	{ MODKEY|ShiftMask,		XK_KP_Add,		spawn,	{.v = (const char*[]){ "change-volume", "-5", NULL } } },
	{ MODKEY|ShiftMask,		XK_KP_Subtract,	spawn,	{.v = (const char*[]){ "change-volume", "+5", NULL } } },

	{ MODKEY,				XK_period,	spawn,		{.v = (const char*[]){ "playerctl", "next", NULL } } },
	{ MODKEY,				XK_comma,	spawn,		{.v = (const char*[]){ "playerctl", "previous", NULL } } },
	{ MODKEY,				XK_c,		spawn,		{.v = (const char*[]){ "notify-calendar", NULL } } },
	// { MODKEY,				XK_y,		spawn,	{.v = (const char*[]){ BROWSER, "--new-window", "https://www.youtube.com/", NULL } } },
	{ MODKEY,				XK_m,		spawn,		{.v = (const char*[]){ "mute-audio", NULL } } },
	{ 0,					XK_Print,	spawn,		{.v = (const char*[]){ "full-screenshot", NULL } } },

	// { MODKEY|ShiftMask,		XK_Print,	spawn,		{.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
	// { MODKEY,			XK_Delete,	spawn,		{.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
	// { MODKEY,			XK_Scroll_Lock,	spawn,		SHCMD("killall screenkey || screenkey &") },

	// { 0, XF86XK_AudioMute,		spawn,		SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	// { 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)") },
	// { 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)") },
	// { 0, XF86XK_AudioPrev,		spawn,		{.v = (const char*[]){ "mpc", "prev", NULL } } },
	// { 0, XF86XK_AudioNext,		spawn,		{.v = (const char*[]){ "mpc",  "next", NULL } } },
	// { 0, XF86XK_AudioPause,		spawn,		{.v = (const char*[]){ "mpc", "pause", NULL } } },
	// { 0, XF86XK_AudioPlay,		spawn,		{.v = (const char*[]){ "mpc", "play", NULL } } },
	// { 0, XF86XK_AudioStop,		spawn,		{.v = (const char*[]){ "mpc", "stop", NULL } } },
	// { 0, XF86XK_AudioRewind,	spawn,		{.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	// { 0, XF86XK_AudioForward,	spawn,		{.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	// { 0, XF86XK_AudioMedia,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	// { 0, XF86XK_AudioMicMute,	spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	/* { 0, XF86XK_PowerOff,		spawn,		{.v = (const char*[]){ "sysact", NULL } } }, */
	// { 0, XF86XK_Calculator,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
	// { 0, XF86XK_Sleep,		spawn,		{.v = (const char*[]){ "sudo", "-A", "zzz", NULL } } },
	// { 0, XF86XK_WWW,		spawn,		{.v = (const char*[]){ BROWSER, NULL } } },
	// { 0, XF86XK_DOS,		spawn,		{.v = termcmd } },
	// { 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	// { 0, XF86XK_TaskPane,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	// { 0, XF86XK_Mail,		spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	// { 0, XF86XK_MyComputer,		spawn,		{.v = (const char*[]){ TERMINAL, "-e",  "lfub",  "/", NULL } } },
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
	// { 0, XF86XK_Launch1,		spawn,		{.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
	// { 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	// { 0, XF86XK_TouchpadOff,	spawn,		{.v = (const char*[]){ "synclient", "TouchpadOff=1", NULL } } },
	// { 0, XF86XK_TouchpadOn,		spawn,		{.v = (const char*[]){ "synclient", "TouchpadOff=0", NULL } } },
	// { 0, XF86XK_MonBrightnessUp,	spawn,		{.v = (const char*[]){ "xbacklight", "-inc", "15", NULL } } },
	// { 0, XF86XK_MonBrightnessDown,	spawn,		{.v = (const char*[]){ "xbacklight", "-dec", "15", NULL } } },

	/* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */
	/* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
	/* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
	/* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	// { ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};

