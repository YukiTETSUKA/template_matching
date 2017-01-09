Template Matching
---

テンプレートマッチングするやつ on MacOS or Linux

Usage
---

Using a template_img
```
$ ./a.out <picture dir> <template picture> <distribution dir>

Example:
$ ./a.out ~/Desktop/work ~/Desktop/template/hoge.png ~/Desktop/template_matching/
```

Using multiple template_imgs
```
$ find <template pictures dir> -type f -exec ./a.out <pictures dir> {} <distribution dir> \;

Example:
$ find ~/Desktop/template -type f -exec ./a.out ~/Desktop/work {} ~/Desktop/template_matching/ \;
```
