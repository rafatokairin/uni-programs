import React from 'react';
import {
  View,
  Text,
  StyleSheet,
  ScrollView,
  TouchableOpacity,
  TouchableWithoutFeedback,
  ImageBackground,
} from 'react-native';

import CenterMessage from './CenterMessage';

class Ability extends React.Component {
  navigate = (item, index) => {
    this.props.navigation.navigate('Dice', { dice: item, index: index, onDiceRoll: this.handleDiceRoll });
  }

  state = {
    info: '',
    selectedOptionIndex: 0,
    options: ['d4', 'd6', 'd12'],
    diceValues: [],
    counter: 0,
  }

  onChangeText = (key, value) => {
    this.setState({
      [key]: value,
    });
  }

  addDice = () => {
    const { ability } = this.props.route.params;
    const selectedOption = this.state.options[this.state.selectedOptionIndex];
    let numberOfSides = 0;

    switch (selectedOption) {
      case 'd4':
        numberOfSides = 4;
        break;
      case 'd6':
        numberOfSides = 6;
        break;
      case 'd12':
        numberOfSides = 12;
        break;
      default:
        numberOfSides = 0;
    }

    const dice = {
      info: selectedOption,
      numberOfSides: numberOfSides,
    };
    const diceValues = [...this.state.diceValues];
    diceValues.push(null);
    this.setState({ diceValues });
    this.props.addDice(dice, ability);
  }

  moveCarouselLeft = () => {
    this.setState(prevState => ({
      selectedOptionIndex: prevState.selectedOptionIndex === 0 ? prevState.options.length - 1 : prevState.selectedOptionIndex - 1,
    }));
  }

  moveCarouselRight = () => {
    this.setState(prevState => ({
      selectedOptionIndex: (prevState.selectedOptionIndex + 1) % prevState.options.length,
    }));
  }

  handleDiceRoll = (randomNumber, index) => {
    const diceValues = [...this.state.diceValues];
    diceValues[index] = randomNumber;
    this.setState({ diceValues });
  }

  getTotalSum = () => {
    const filteredDiceValues = this.state.diceValues.filter(value => value !== null);
    const totalSum = filteredDiceValues.reduce((acc, curr) => acc + curr, 0);
    return totalSum + this.state.counter;
  }

  incrementCounter = () => {
    this.setState(prevState => ({
      counter: prevState.counter + 1,
    }));
  }

  decrementCounter = () => {
    if (this.state.counter > 0) {
      this.setState(prevState => ({
        counter: prevState.counter - 1,
      }));
    }
  }

  render() {
    const { ability } = this.props.route.params;
    return (
      <ImageBackground source={require('../img/bkg.jpg')} style={styles.background}>
        <View style={styles.container}>
          <ScrollView contentContainerStyle={[styles.dicesContainer, !ability.dices.length && { flex: 1, justifyContent: 'center' }]}>
            {
              !ability.dices.length && <CenterMessage message='No dices for this ability!' />
            }
            {
              ability.dices.map((dice, index) => (
                <TouchableWithoutFeedback onPress={() => this.navigate(dice, index)} key={index} >
                  <View key={index} style={styles.diceContainer}>
                    <Text style={styles.diceInfo}>{dice.info}</Text>
                    <Text style={styles.randomNumber}>{this.state.diceValues[index]}</Text>
                  </View>
                </TouchableWithoutFeedback>
              ))
            }
            <View style={styles.totalContainer}>
              <Text style={styles.totalText}>Total: {this.getTotalSum()}</Text>
              <View style={styles.counterContainer}>
                <TouchableOpacity onPress={this.decrementCounter} style={styles.counterButton}>
                  <Text style={styles.counterButtonText}> - </Text>
                </TouchableOpacity>
                <Text style={styles.counterText}>{this.state.counter}</Text>
                <TouchableOpacity onPress={this.incrementCounter} style={styles.counterButton}>
                  <Text style={styles.counterButtonText}> + </Text>
                </TouchableOpacity>
              </View>
            </View>
          </ScrollView>
          <View style={styles.buttonContainer}>
            <View style={styles.carouselContainer}>
              <TouchableOpacity onPress={this.moveCarouselLeft} style={styles.arrowButton}>
                <Text style={styles.arrowText}>{'<'}</Text>
              </TouchableOpacity>
              <Text style={styles.carouselText}>{this.state.options[this.state.selectedOptionIndex]}</Text>
              <TouchableOpacity onPress={this.moveCarouselRight} style={styles.arrowButton}>
                <Text style={styles.arrowText}>{'>'}</Text>
              </TouchableOpacity>
            </View>
            <TouchableOpacity onPress={this.addDice} style={styles.button}>
              <Text style={styles.buttonText}>Add Dice</Text>
            </TouchableOpacity>
          </View>
        </View>
      </ImageBackground>
    );
  }
}

const styles = StyleSheet.create({
  background: {
    flex: 1,
    resizeMode: "cover",
    justifyContent: "center"
  },
  container: {
    flex: 1
  },
  dicesContainer: {
    paddingBottom: 104
  },
  buttonContainer: {
    position: 'absolute',
    bottom: 0,
    left: 0,
    width: '100%',
    alignItems: 'center',
  },
  button: {
    width: '100%',
    height: 50,
    backgroundColor: '#e8def8',
    justifyContent: 'center',
    alignItems: 'center',
    marginTop: 2,
  },
  buttonText: {
    color: 'black'
  },
  diceContainer: {
    padding: 16,
    borderBottomColor: 'rgba(0, 0, 0, .5)',
    borderBottomWidth: 2,
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center',
  },
  diceInfo: {
    fontSize: 20,
    color: 'rgba(0, 0, 0, .5)'
  },
  randomNumber: {
    fontSize: 20,
    color: 'rgba(0, 0, 0, .5)'
  },
  totalContainer: {
    paddingVertical: 16,
    paddingHorizontal: 20,
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center',
  },
  totalText: {
    color: 'rgba(0, 0, 0, .5)',
    fontSize: 20,
    fontWeight: 'bold',
  },
  carouselContainer: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    paddingHorizontal: 20,
    alignItems: 'center',
    backgroundColor: '#800000',
    height: 50,
    width: '100%',
  },
  carouselText: {
    color: 'white',
  },
  arrowButton: {
    padding: 10,
  },
  arrowText: {
    color: 'white',
  },
  counterContainer: {
    flexDirection: 'row',
    alignItems: 'center',
    marginTop: 10,
  },
  counterButton: {
    backgroundColor: 'rgba(0, 0, 0, .5)',
    padding: 10,
    borderRadius: 5,
  },
  counterButtonText: {
    fontSize: 20,
    color: '#e8def8'
  },
  counterText: {
    color: 'rgba(0, 0, 0, .5)',
    fontSize: 20,
    marginHorizontal: 10,
  },
});

export default Ability;