
/*
 * Copyright (C) Nigel Baillie <nigelbaillie@hey.com>
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


typedef struct {
    /* TODO: what do we need!!?? */
    ngx_uint_t enabled;
} ngx_http_webapp_loc_conf_t;


/* config constructor */
static void *
ngx_http_webapp_create_loc_conf(ngx_conf_t *cf);

/* config merger */
static char *
ngx_http_webapp_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child);

/* "webapp" config directive callback */
static char *
ngx_http_webapp(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

/* handler */
static ngx_int_t
ngx_http_webapp_handler(ngx_http_request_t *r);


/*
 * I guess this is the v-table for the object that handles sysadmin input
 * in the form of nginx config.
 */
static ngx_http_module_t  ngx_http_webapp_module_ctx = {
    NULL,                          /* preconfiguration */
    NULL,                          /* postconfiguration */

    NULL,                          /* create main configuration */
    NULL,                          /* init main configuration */

    NULL,                          /* create server configuration */
    NULL,                          /* merge server configuration */

    ngx_http_webapp_create_loc_conf,  /* create location configuration */
    ngx_http_webapp_merge_loc_conf /* merge location configuration */
};


/*
 * The new nginx config "commands" introduced by this module.
 */
static ngx_command_t  ngx_http_webapp_commands[] = {
    { ngx_string("webapp"),
      NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
      ngx_http_webapp,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

      ngx_null_command
};


/*
 * Main configuration for the module? 
 */
ngx_module_t  ngx_http_webapp_module = {
    NGX_MODULE_V1,
    &ngx_http_webapp_module_ctx, /* module context */
    ngx_http_webapp_commands,   /* module directives */
    NGX_HTTP_MODULE,               /* module type */
    NULL,                          /* init master */
    NULL,                          /* init module */
    NULL,                          /* init process */
    NULL,                          /* init thread */
    NULL,                          /* exit thread */
    NULL,                          /* exit process */
    NULL,                          /* exit master */
    NGX_MODULE_V1_PADDING
};


/*
 * This is the handler for the "webapp" configuration directive!
 */
static char *
ngx_http_webapp(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
    ngx_http_webapp_loc_conf_t *webapp_cf = conf;
    ngx_http_core_loc_conf_t  *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_webapp_handler;

    printf("THANK YOU!!\n");

    webapp_cf->enabled = 1;

    return NGX_CONF_OK;
}


static ngx_int_t
ngx_http_webapp_handler(ngx_http_request_t *r) {
    ngx_http_webapp_loc_conf_t  *webapp_cf;
    webapp_cf = ngx_http_get_module_loc_conf(r, ngx_http_webapp_module);

    /* TODO: do real work here?? */
    if (webapp_cf->enabled) {
        return NGX_HTTP_FORBIDDEN;
    }
    else {
        return NGX_HTTP_NO_CONTENT;
    }
}


/*
 * This bad boy is just for allocating our loc_conf_t and initializing values.
 *
 * It's basically the constructor.
 */
static void *
ngx_http_webapp_create_loc_conf(ngx_conf_t *cf)
{
    ngx_http_webapp_loc_conf_t  *conf;

    printf("this is ok right?\n");

    /* ngx_pcalloc and ngx_palloc will be freed by nginx */
    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_webapp_loc_conf_t));
    if (conf == NULL) {
        return NGX_CONF_ERROR;
    }
    conf->enabled = 0;
    return conf;
}


/*
 * This is where we can initialize things that require some heavy lifting
 * I guess.
 *
 * Maybe in my case, I can load the mysql dynamic lib and store function
 * pointers to it.
 */
static char *
ngx_http_webapp_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child) {
    ngx_http_webapp_loc_conf_t *prev = parent;
    ngx_http_webapp_loc_conf_t *conf = child;

    ngx_conf_merge_uint_value(conf->enabled, prev->enabled, 0);

    /* TODO: how2 handle error:
    if (conf->max_radius < conf->min_radius) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, 
            "max_radius must be equal or more than min_radius");
        return NGX_CONF_ERROR;
    }
    */

    return NGX_CONF_OK;
}
