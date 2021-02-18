module.exports = {
  title: 'Miguel\'s Blog',
  description: 'Well, hello.',
  theme: '@vuepress/theme-blog', // OR shortcut: @vuepress/blog
  // theme: "blog-vuetify",

  markdown: {
    extendMarkdown: md => {
      md.use(require("markdown-it-katex"));
    }
  },

  head: [
    ['link', { rel: 'stylesheet', href: 'https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.5.1/katex.min.css' }],
    ['link', { rel: 'stylesheet', href: 'https://cdn.jsdelivr.net/github-markdown-css/2.2.1/github-markdown.css' }]
  ],

  themeConfig: {
    /**
     * Ref: https://vuepress-theme-blog.ulivz.com/#modifyblogpluginoptions
     */
    modifyBlogPluginOptions(blogPluginOptions) {
      return blogPluginOptions
    },
    /**
     * Ref: https://vuepress-theme-blog.ulivz.com/#nav
     */
    nav: [
      {
        text: '文章',
        link: '/',
      },
      {
        text: 'Tags',
        link: '/tag/',
      },
    ],
    /**
     * Ref: https://vuepress-theme-blog.ulivz.com/#footer
     */
    footer: {
      contact: [
        {
          type: 'github',
          link: 'https://github.com/miguch',
        },
        // {
        //   type: 'twitter',
        //   link: 'https://twitter.com/_ulivz',
        // },
      ],
      copyright: [
        {
          text: 'Privacy Policy',
          link: '/2021/02/18/privacypolicy/',
        },
        // {
        //   text: 'MIT Licensed | Copyright © 2018-present Vue.js',
        //   link: '',
        // },
      ],
    },
  },
}
