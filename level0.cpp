/*
 * level0.cpp - the first (and only) level!
 */

#include <iostream>
#include <string>

#include "messages.h"
#include "errmessages.h"
#include "level.h"
#include "characters.h"
#include "command.h"


static void setup_lang(Level& lvl)
{
	StringTable tbl;
	tbl["help"] =
		"Here are the available commands. Arguments with <angle> brackets are\n"
		"mandatory, while arguments with [square] brackets are optional.\n\n"

		" - help             print this message.\n"
		" - attack <target>  attack the target named \"target\".\n"
		" - look [target]    without a [target], look around. Otherwise examine\n"
		"                    the [target] more closely.\n"
		" - exit             exit the game.\n";

	tbl["default"] =
		"After forcing the rotted, once-elaborate door ajar, you step through\n"
		"the darkness beyond the yawning portcullis. Time has claimed this\n"
		"once-great castle. All that now reigns is vegetation and animal waste.\n"
		"You decide to push the large door further from the inside to let in\n"
		"more light. Your heart skips a beat. A gaunt figure slowly raises\n"
		"from a kneeling position and shuffles toward you.\n\n"

		"\"Was it...feeding?\" you absently think out loud.\n\n";

	tbl["ghoul"] =
		"Your steady, well-trained hand reaches toward your blade. You realize\n"
		"now the rumors you heard aren't merely the ravings of the\n"
		"superstitious drunkards back in town. Unfortunately, this thing is\n"
		"standing between you and a nice payday. Beyond dilapidated antechamber,\n"
		"you spot fabled MacGuffin Crystal. It looks like this ghoul is going\n"
		"to have to die.\n\n";

	tbl["attackable"] = "Attackable Enemies:\n";
	tbl["enemy_item"] = "  - %s\n";
	tbl["prompt"] = "%s> ";

	lvl.initmessages(tbl);
}


/*
 * TODO: this is where we're going to establish the command table and
 * player objects. The entry point will invoke level-start functions.
 */
