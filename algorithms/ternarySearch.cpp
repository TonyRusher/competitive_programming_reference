for(int j = 0;j < 300; j++){
	ld mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3;
	ld f1 = f(p0, Friend1[i + 1], p1, Friend2[i + 1], mid1);
	ld f2 = f(p0, Friend1[i + 1], p1, Friend2[i + 1], mid2);
	if(f1 >= f2) l = mid1;
	else r = mid2;
}