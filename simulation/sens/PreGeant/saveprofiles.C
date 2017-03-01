/*
 * 1 - "best case"
 * 2 - bd + 1 MeV decay energy
 * 3 - glauber kick A
 * 4 - glauber kick B
 * 5 - increased angle widths
 * 6 - increased dbe
 * 7 - increased x,y widhts
 * 8 - target
*/
{
char base[512];
char file[1024];

sprintf(base,"PB%i",8);

sprintf(file,"%s_b%i",base,2);
savefig("c1",file);

sprintf(file,"%s_c%iDV",base,1);
savefig("c2",file);

sprintf(file,"%s_c%iDV",base,2);
savefig("c4",file);

sprintf(file,"%s_txty",base);
savefig("c6",file);

sprintf(file,"%s_KEvel",base);
savefig("c20",file);

sprintf(file,"%s_vrel",base);
savefig("c21",file);
/*
*/
sprintf(file,"%s_path1D",base);
savefig("c30",file);

sprintf(file,"%s_path2D",base);
savefig("c31",file);

}
