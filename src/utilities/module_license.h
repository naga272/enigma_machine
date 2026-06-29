#ifndef MODULE_LICENSE_H
#define MODULE_LICENSE_H

/*
* idea presa dal kernel di linux :3
*
* ES: MODULE_LICENSE("GPL-3.0");
* diventa:
* static const char mod_license[] = "license=GPL-3";
*
* viene inserito nella sezione .modinfo del binario, quindi alla fine vedremo in quella sezione:
* "license=GPL-3.0"
*
* MODULE_AUTHOR("naga272");
* diventa:
*
* static const char mod_author[] = "author=naga272";
* viene inserito nella sezione .modinfo del binario, quindi alla fine vedremo in quella sezione:
* "author=naga272"
**/


#define MODULE_INFO(tag, info) \
    static const char mod_##tag[] \
        __attribute__((used, section(".modinfo"))) = \
        #tag "=" info


#define MODULE_LICENSE(_license) MODULE_INFO(license, _license)
#define MODULE_DESCRIPTION(_description) MODULE_INFO(description, _description)
#define MODULE_AUTHOR(_author) MODULE_INFO(author, _author)


#endif