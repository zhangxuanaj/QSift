//
// Created by Guilherme Wachs on 08/03/16.
//

#include <sift.h>

#include <highgui.h>
#include <imgfeatures.h>
#include <utils.h>

IplImage *resizeIpl(IplImage *img, float factor){
    CvSize s = cvGetSize(img);
    s.height *= factor;
    s.width *= factor;

    IplImage *ret = cvCreateImage( s, img->depth, img->nChannels);
    cvResize(img, ret);
    return ret;
}


int main(int argc, char *argv[]) {

    //IplImage *img = cvLoadImage("/Users/wachs/SUN/Images/a/abbey/sun_aaalbzqrimafwbiv.jpg", CV_LOAD_IMAGE_COLOR);
    IplImage *orig = cvLoadImage("/Users/wachs/Dropbox/SIFT/CPP/OpenSift/sbc1.png", CV_LOAD_IMAGE_COLOR);
    IplImage *orig2 = cvLoadImage("/Users/wachs/Dropbox/SIFT/CPP/OpenSift/sbc2.png", CV_LOAD_IMAGE_COLOR);

    IplImage *img=resizeIpl(orig, 0.25);
    IplImage *img2=resizeIpl(orig2, 0.25);

    cvReleaseImage(&orig);
    cvReleaseImage(&orig2);

    struct feature *feat;

    /*int points = _sift_features( img, &feat, SIFT_INTVLS, SIFT_SIGMA, SIFT_CONTR_THR,
                           SIFT_CURV_THR, SIFT_IMG_DBL, SIFT_DESCR_WIDTH,
                           SIFT_DESCR_HIST_BINS );*/

    int points = _sift_features(img, &feat, SIFT_INTVLS, SIFT_SIGMA, SIFT_CONTR_THR,
                           SIFT_CURV_THR, SIFT_IMG_DBL, SIFT_DESCR_WIDTH,
                           SIFT_DESCR_HIST_BINS, 0, NULL,NULL );
    printf("%d\n", points);
    for(int i=0; i<10; i++){
        printf("x: %-4.0f  %-4.0f\n", feat[i].x, feat[i].y);
        cvCircle(img, cvPoint(feat[i].x,feat[i].y), 5, cvScalar(0,0,255,0), 2);
    }
    cvShowImage("img1", img);
    free(feat);

    points = _sift_features( img2, &feat, SIFT_INTVLS, SIFT_SIGMA, SIFT_CONTR_THR,
                                 SIFT_CURV_THR, SIFT_IMG_DBL, SIFT_DESCR_WIDTH,
                                 SIFT_DESCR_HIST_BINS, 0, NULL,NULL );
    printf("%d\n", points);
    for(int i=0; i<10; i++){
        printf("x: %-4.0f  %-4.0f\n", feat[i].x, feat[i].y);
        cvCircle(img2, cvPoint(feat[i].x,feat[i].y), 5, cvScalar(0,0,255,0), 2);
    }
    cvShowImage("img2", img2);

    free(feat);

    cvWaitKey(0);

    cvReleaseImage(&img);
    cvReleaseImage(&img2);

    return 0;
}
