[num,txt] = xlsread('E:\GitHub\Birdy-Mathematical-Modelling-Group\20220218_MCM_2022\Notes\Table1_TreeDatasetAge.xlsx',1,'A1:F14488');
age = []; dbh = []; treeHtm = []; CrnHtm = []; treeTyp = []; leaveArea = []; chunkVol = [];
for i=1:size(num,1)
    age = [age, num(i,1)];
    dbh = [dbh, num(i,2)];
    treeHtm = [treeHtm, num(i,3)];
    CrnHtm = [CrnHtm, num(i,4)];
    treeTyp = [treeTyp, txt(i,5)];
    leaveArea = [leaveArea, num(i,6)];
end
for i=1:size(num,1)
    chunkVol = [chunkVol, pi * dbh(i) * dbh(i) / 4 * (treeHtm(i) - CrnHtm(i)) / 10000];
end
cftool(age,leaveArea)