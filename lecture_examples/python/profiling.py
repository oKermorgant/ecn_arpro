import cv2
import pylab as pl
#import cProfile
#import pstats

#profiler = cProfile.Profile()
#profiler.enable()

#@profile
def filter_opencv(im):
    '''
    Do some filtering with OpenCV
    '''
    # cvt to gray level
    img = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
    
    # Kernel filter
    return cv2.GaussianBlur(img, (3,3), 1) 

#@profile
def filter_homemade(im):
    
    h,w = im.shape[0],im.shape[1]
    
    # cvt to gray level
    img = pl.zeros((h,w))
    for i in xrange(h):
        for j in xrange(w):
            img[i,j] = int(pl.mean(im[i,j]))
            
    # low pass filter
    Ker = 1./16 * pl.array([[1,2,1],[2,4,2],[1,2,1]])
    imf = pl.uint8(img.copy())
    for i in xrange(1,h-1):
	for j in xrange(1,w-1):
		imf[i,j] = int(pl.sum(Ker * img[i-1:i+2,j-1:j+2]))
    
    return imf 
    

im = cv2.imread('lenna.png')

cv2.imshow('Manual', filter_homemade(im))
cv2.imshow('OpenCV', filter_opencv(im))
cv2.waitKey(0)

#profiler.create_stats()
#stats = pstats.Stats(profiler)
#stats.strip_dirs().sort_stats('cumulative').dump_stats('stats.prof')
