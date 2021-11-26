# To use

Make sure your current working directory is the nginx project root.

First, compile nginx with this module added:

```bash
auto/configure --add-module=$PWD/custom/webapp
```

Next, start up nginx

```bash
objs/nginx -p $PWD/custom/webapp/demo/
```

# Protips

Alias nginx, as it's daemonized always

```bash
alias nginx="objs/nginx -p $PWD/custom/webapp/demo/"
```
