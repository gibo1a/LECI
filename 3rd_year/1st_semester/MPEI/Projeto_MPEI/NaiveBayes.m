classdef NaiveBayes
    methods(Static)
        %Creates a matrix with the documents as the columns and the words as the lines, this matrix has the count of every word for each document.
        function document_matrix = createDocumentMatrix(data,unique_words)
            document_matrix = zeros(size(unique_words,1),size(data,1));
            for i = 1:size(data,1)
                %line = strjoin(data(i,:));
                value = data(i, :);
                line = ''; 
                for idx = 1:size(value, 2)
                    line = [line, value{1, idx}, ' ']; 
                end
                line = strtrim(line);
                for j = 1:length(unique_words)
                    if contains(line,unique_words{j})
                        document_matrix(j,i) = document_matrix(j,i) + 1;
                    end
                end
            end
        end
        
        %Splits the data into training and testing data.
        function [train,test,train_categories,test_categories] = splitTrainTestData(data,train_percentage,test_percentage,categories)
            train_indices = randperm(round(size(data,2).*train_percentage));
            train = data(:,train_indices);
            train_categories = categories(train_indices,:);
            test_indices = randperm(round(size(data,2).*test_percentage));
            test = data(:,test_indices);
            test_categories = categories(test_indices,:);
        end
        
        %Calculates the probability of a document being of class LIKE or class DISLIKE.
        function class_probabilities = calculateClassProbabilities(train_categories)
            p_like = length(train_categories((train_categories == 'LIKE')))./length(train_categories);
            p_dislike = length(train_categories((train_categories == 'DISLIKE')))./length(train_categories);
            class_probabilities = [p_like,p_dislike];
        end
        
        %Calculates the conditional probabilities of each unique word.
        function [probabilities_LIKE,probabilities_DISLIKE] = calculateConditionalProbabilities(unique_words,train_data,train_categories)
            probabilities_LIKE = zeros(1,length(unique_words));  
            probabilities_DISLIKE = zeros(1,length(unique_words)); 
            for i = 1:length(unique_words)
                probabilities_LIKE(i) = (sum(train_data(i,train_categories == 'LIKE')) +1) ./(length(train_categories((train_categories == 'LIKE'))) + length(unique_words));
                probabilities_DISLIKE(i) = (sum(train_data(i,train_categories == 'DISLIKE')) +1) ./(length(train_categories((train_categories == 'DISLIKE'))) + length(unique_words));
            end
        end
        
        %Predicts the classes of the items.
        function predictedClassifications = classify(items,probabilities_LIKE,probabilities_DISLIKE,classes_probabilities,unique_words)
            predictedClassifications = categorical(repmat({'LIKE'}, size(items,2), 1)); 
            p_LIKE = classes_probabilities(1);
            p_DISLIKE = classes_probabilities(2);
            for i = 1:size(items,2)
                song = items(:,i);      
                for j = 1:length(unique_words)
                    if song(j) >= 1
                        p_LIKE = p_LIKE * probabilities_LIKE(j);
                        p_DISLIKE = p_DISLIKE * probabilities_DISLIKE(j);
                    end
                end
                if p_LIKE > p_DISLIKE
                    predictedClassifications(i) = 'LIKE';
                else
                    predictedClassifications(i) = 'DISLIKE';
                end
            end
        end
    end
end