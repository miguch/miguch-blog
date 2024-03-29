# 1. build frontend code
FROM node:14.16.0 AS build-stage
COPY . .
RUN yarn
RUN yarn build

# 2. start nginx server to serve static files
FROM nginx:1.21 AS serve-stage
COPY --from=build-stage /blog/.vuepress/dist/ /usr/share/nginx/html
COPY --from=build-stage /nginx.conf /etc/nginx/conf.d/default.conf
CMD sed -i -e 's/$PORT/'"$PORT"'/g' /etc/nginx/conf.d/default.conf && nginx -g 'daemon off;'
