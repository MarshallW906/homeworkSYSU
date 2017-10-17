##使table可sort
15331302 王翔宇

```javascript
$(document).on('click','th', function() {var table = $(this).parents('table').eq(0);var rows = table.find('tr:gt(0)').toArray().sort(function() {return function(a, b) {var valA = $(a).children('td').eq($(this).index()).text(), valB = $(b).children('td').eq($(this).index()).text();return $.isNumeric(valA) && $.isNumeric(valB) ? valA - valB : valA.localeCompare(valB);};});this.asc = !this.asc;if (!this.asc) rows = rows.reverse();table.children('tbody').empty().html(rows);});
```

###sample pages
http://v3.bootcss.com/getting-started/#support
http://acdream.info/problem/list
http://acm.uestc.edu.cn/#/problem/list
https://www.codechef.com/problems/school