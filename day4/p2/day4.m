%goofy solution using matlab and convolution

% Load the text file and parse into matrix
filename = 'input4.txt';
fileData = fileread(filename);
rows = splitlines(fileData);
numRows = numel(rows);
mat = zeros(numRows, max(cellfun(@length, rows)));
for i = 1:numRows
    for j = 1:length(rows{i}) 
        mat(i, j) = double(rows{i}(j));  
    end
end

%start a counter and define the base kernal
count = 0;
ogker = [double('S') 0 double('S');
           0 double('A') 0;
         double('M') 0 double('M')];

for n=0:3
    %rotate the kernal to new orientation
    ker = rot90(ogker, n);

    convolution = conv2(mat, ker, 'valid');
    kernel_sum = sum(ker(:).^2);

    result = (convolution == kernel_sum);
    
    count = count + sum(result(:)); %Total count of x - mas matches
end
disp(count)