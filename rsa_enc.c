#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "rsa.h"
#include "rsa_num.h"

#ifndef RSA_MASTER
static opt_t options_encrypter[] = {
    {RSA_OPT_FILE, 'f', "file", required_argument, "input file to encrypt"},
    {RSA_OPT_LEVEL, 'l', "level", required_argument, "set encryption level to "
	"128, 256, 512 or 1024 (default)"},
    {RSA_OPT_RSAENC, 'r', "rsa", no_argument, "full RSA encryption. if this "
	"flag is not set, encryption will be done using a symmetric "
	"key and only it will be RSA encrypted"},
    { RSA_OPT_MAX }
};

/* encryption task is to be performed */
static rsa_errno_t parse_args_finalize_encrypter(int *flags, int actions)
{
    if (!actions)
	*flags |= OPT_FLAG(RSA_OPT_ENCRYPT);

    /* test for non compatable options with encrypt */
    if ((*flags & OPT_FLAG(RSA_OPT_ENCRYPT)) && 
	!(*flags & OPT_FLAG(RSA_OPT_FILE)))
    {
	return RSA_ERR_NOFILE;
    }

    return RSA_ERR_NONE;
}

static rsa_errno_t parse_args_encrypter(int opt, int *flags)
{
    switch (opt_short2code(options_encrypter, opt))
    {
    case RSA_OPT_FILE:
	OPT_ADD(flags, RSA_OPT_FILE, rsa_set_file_name(optarg));
	break;
    case RSA_OPT_LEVEL:
	OPT_ADD(flags, RSA_OPT_LEVEL);
	if (rsa_encryption_level_set(optarg))
	    return RSA_ERR_LEVEL;
	break;
    case RSA_OPT_RSAENC:
	OPT_ADD(flags, RSA_OPT_RSAENC);
	break;
    default:
	return RSA_ERR_OPTARG;
    }

    return RSA_ERR_NONE;
}

int main(int argc, char *argv[])
{
    int err, action, flags = 0;
    rsa_handler_t encrypter_handler = {
	.keytype = RSA_KEY_TYPE_PUBLIC,
	.options = options_encrypter,
	.ops_handler = parse_args_encrypter,
	.ops_handler_finalize = parse_args_finalize_encrypter,
    };

    if ((err = parse_args(argc, argv, &flags, &encrypter_handler)) != 
	RSA_ERR_NONE)
    {
	return rsa_error(argv[0], err);
    }

    action = rsa_action_get(flags, RSA_OPT_ENCRYPT, NULL);
    switch (action)
    {
    case OPT_FLAG(RSA_OPT_ENCRYPT):
    {
	if (flags & OPT_FLAG(RSA_OPT_LEVEL))
	    RSA_TBD("handle RSA_OPT_LEVEL");
	if (flags & OPT_FLAG(RSA_OPT_RSAENC))
	    RSA_TBD("handle RSA_OPT_RSAENC");

	RSA_TBD("handle RSA_OPT_ENCRYPT");
	break;
    }
    default:
	return rsa_action_handle_common(action, argv[0], &encrypter_handler);
    }

    return 0;
}
#endif
