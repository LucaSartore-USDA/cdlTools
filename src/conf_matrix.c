#include "myomp.h"
#include <gdal.h>
#include <cpl_conv.h>
#include "conf_matrix.h"

/**
 * @breif Confusion matrix between two raster files
 * @param cdl Location of the classification raster
 * @param truth Location of the ground-reference
 * @param mat A 256-by-256 matrix of zero integers
 */
void conf_matrix(char **cdl, char **truth, int *mat) {
	unsigned char *cbuf, *tbuf;
	int xcdl, xtrt, ycdl, ytrt;
	GDALDatasetH hcdl, htrt;
	GDALRasterBandH cbnd, tbnd;
	int i, j;
	CPLErr erc, ert;
	
	GDALAllRegister();
	hcdl = GDALOpen(*cdl, GA_ReadOnly);
	htrt = GDALOpen(*truth, GA_ReadOnly);
	
	xcdl = GDALGetRasterXSize(hcdl);
	ycdl = GDALGetRasterYSize(hcdl);
	xtrt = GDALGetRasterXSize(htrt);
	ytrt = GDALGetRasterYSize(htrt);
	
	if (xcdl != xtrt || ycdl != ytrt) return;	
	cbuf = CPLMalloc(xcdl * sizeof(char));
	tbuf = CPLMalloc(xcdl * sizeof(char));
	
	if (cbuf && tbuf) {
		cbnd = GDALGetRasterBand(hcdl, 1);
		tbnd = GDALGetRasterBand(htrt, 1);
		for (i = 0; i < ycdl; i++) {
			erc = GDALRasterIO(cbnd, GF_Read, 0, 0, xcdl, i + 1, cbuf, xcdl, 1, GDT_Byte, 0, 0);
			ert = GDALRasterIO(tbnd, GF_Read, 0, 0, xcdl, i + 1, tbuf, xcdl, 1, GDT_Byte, 0, 0);
			if (!erc && !ert) {
				_pragma(omp parallel for default(shared) private(j))
				for (j = 0; j < xcdl; j++) {
					_pragma(omp atomic)
					mat[256 * tbuf[j] + cbuf[j]]++;
				}
			}
		}
		CPLFree(cbuf);
		CPLFree(tbuf);
	}
	GDALClose(hcdl);
	GDALClose(htrt);
}
