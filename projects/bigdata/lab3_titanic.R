
titanic <- read.csv('titanic_train.csv')

# 1
sex_count <- c('Male' = sum(titanic$Sex == 'male'), 'Female' = sum(titanic$Sex == 'female'))
sex_count

# 2
hist(titanic$Pclass, main = 'Class')
hist(titanic$Pclass[titanic$Sex == 'male'], main = 'Male class')
hist(titanic$Pclass[titanic$Sex == 'female'], main = 'Female class')
man_second_class <- sum(titanic$Sex == 'male' & titanic$Pclass == 2)
c('Man in 2 class' = man_second_class)

# 3
fare_median <- round(median(titanic$Fare), digits = 2)
fare_sd <- round(sd(titanic$Fare), digits = 2)
c('Fare median' = fare_median, 'Fare deviation' = fare_sd)

# 4
no_na_age <- titanic[!is.na(titanic$Age),]
under_30 <- no_na_age$Survived[no_na_age$Age < 30]
after_60 <- no_na_age$Survived[no_na_age$Age > 60]
ration_under_30 <- sum(under_30) / length(under_30)
ration_after_60 <- sum(after_60) / length(after_60)
c('Under 30' = ration_under_30, 'After 60' = ration_after_60)
cat('Statement "People under 30 survived more often" is', ration_under_30 > ration_after_60)

# 5
ratio_male <- sum(titanic$Sex == 'male' & titanic$Survived == 1) / sex_count['Male']
ratio_female <- sum(titanic$Sex == 'female' & titanic$Survived == 1) / sex_count['Female']
c('Male ratio' = ratio_male, 'Female ration' = ratio_female)
cat('Statement "Women survived more than men" is', ratio_female > ratio_male)

# 6
names_vector <- sapply(titanic$Name, function(s){strsplit(s, ' ')[[1]][3]})
male_names <- table(names_vector[titanic$Sex == 'male'])
cat('Most popular name is', names(male_names[male_names == max(male_names)]))

# 7
plot(titanic$Fare[titanic$Survived == 1])
plot(titanic$Fare[titanic$Survived == 0])
survived_age <- titanic$Age[titanic$Survived == 1 & !is.na(titanic$Age)]
died_age <- titanic$Age[titanic$Survived == 0 & !is.na(titanic$Age)]
plot(survived_age)
plot(died_age)
cat('Statement "Mean age of died people is higher" is', mean(died_age) > mean(survived_age))

# 8
no_na_age <- titanic[!is.na(titanic$Age),]
mean_age <- function (gender) {
  sapply(1:3, function(cl) {
    mean(no_na_age$Age[no_na_age$Pclass == cl & no_na_age$Sex == gender])
  })
}

plot(x = 1:3, y = mean_age('male'), type = 'b', xlab = 'Class', ylab = 'Mean age', main = 'Men')
plot(x = 1:3, y = mean_age('female'), type = 'b', xlab = 'Class', ylab = 'Mean age', main = 'Women')

# 9
passengers_ratio <- function (airport) {
  gender <- titanic$Sex[titanic$Embarked == airport]
  sum(gender == 'female') / length(gender)
}

airports <- c('Cherbourg' = 'C', 'Southampton' = 'S', 'Queenstown' = 'Q')
ratio <- sapply(airports, passengers_ratio)
cat('Most ratio was in', names(ratio[ratio == max(ratio)]), 'airport')

# 10
siblings <- aggregate(titanic$Survived, by = list(titanic$SibSp), mean)
plot(siblings, type = 'b', xlab = 'Siblings count', ylab = 'Chance to survive')

parch <- aggregate(titanic$Survived, by = list(titanic$Parch), mean)
plot(parch, type = 'b', xlab = 'Siblings count', ylab = 'Chance to survive')


