# -*- coding: UTF-8 -*-
import urllib, urllib2
import lxml
from bs4 import BeautifulSoup

import types
import difflib
import sys

start_url = 'http://blog.csdn.net/c406495762/article/details/71158264'
dest_url = 'http://www.biqukan.com/1_1094/16290300.html'
currentDepthLimit = 0

visitPages = set()


def dfs(currentURL, currentDepth, parentURL = ""):
    if currentURL == dest_url:
        return True

    # if predict cannot reach dest_url  return false
    if currentDepth > currentDepthLimit:
        return False

    cur_req = urllib2.Request(url = currentURL)
    cur_req.add_header('User-Agent', "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36")

    try:
        target_response = urllib2.urlopen(cur_req)
        target_html = target_response.read().decode('utf-8','ignore')
        soup = BeautifulSoup(target_html,'lxml')

        currentUri = currentURL[:currentURL.rindex('/')]
        if currentURL.rindex('/') + 1 == len(currentURL):
            currentUri = currentUri[:currentUri.rindex('/')]

        # find next
        # exclude:
        # begin with '#'
        # javascript:void(0);
        # same link as current url
        # None
        #
        # begin with '/' need to add the current parent uri

        print 'currentDepth:', currentDepth
        global visitPages
        childs = []
        for link in soup.find_all('a'):
            tmpHref = link.get('href')
            if type(tmpHref) is types.NoneType:
                continue
            # print tmpHref
            try:
                if not (tmpHref[0] == '#' or tmpHref.find('javascript:') != -1 or tmpHref == currentURL):
                    if tmpHref[0] == '/':
                        tmpHref = ''.join([currentUri, tmpHref])
                    if not (tmpHref in visitPages):
                        visitPages.add(tmpHref)
                        childs.append(tmpHref)
            except IndexError, e:
                pass

        # difflib.SequenceMatcher(None, a, b)
        childs.sort(key=(lambda str: difflib.SequenceMatcher(None, str, dest_url).ratio() ), reverse=True)
        print 'childs.length:', len(childs)

        for next_url in childs[0:300]:
            if next_url == currentURL:
                continue
            print next_url
            if dfs(next_url, currentDepth + 1, currentURL):
                print 'Find Path:', next_url, '<-', currentURL
                return True
    except urllib2.HTTPError,e:
        print e.code

    return False


def iter_deepening_dfs():
    global currentDepthLimit, visitPages
    currentDepthLimit = 1
    while (not dfs(start_url, 0)):
        if currentDepthLimit > 140:
            print 'out of limit, failed'
            break
        visitPages.clear()
        print currentDepthLimit, 'Failed'
        currentDepthLimit += 1
    return currentDepthLimit + 1


if __name__ == "__main__":
    reload(sys)
    sys.setdefaultencoding('utf-8')
    depth = iter_deepening_dfs()
    print 'depth', depth
