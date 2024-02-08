void floydWarshall(vvi &mtx){
	int n = mtx.size();
	fore(k,0,n) fore(i,0,n) fore(j,0,n)
		mtx[i][j] = min(mtx[i][j], mtx[i][k] + mtx[k][j]);
}