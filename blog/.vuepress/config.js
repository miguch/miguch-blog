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
    // Adsense
    ['script', {
      'data-ad-client': 'ca-pub-9539082383597390',
      async: true,
      src: 'https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js'
    }],
    // Google Analytics
    ['script', {
      async: true,
      src: 'https://www.googletagmanager.com/gtag/js?id=UA-135644242-1'
    }],
    ['script', {}, `
  window.dataLayer = window.dataLayer || [];
  function gtag(){dataLayer.push(arguments);}
  gtag('js', new Date());
  gtag('config', 'UA-135644242-1');
    `],
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
