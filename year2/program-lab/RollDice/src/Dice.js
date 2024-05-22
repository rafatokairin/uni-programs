import React, { Component } from 'react';
import { Dimensions, PanResponder, View, Text, ImageBackground, StyleSheet } from 'react-native';

const { width, height } = Dimensions.get('window');

export default class Dice extends Component {
  constructor(props) {
    super(props);
    this.state = {
      isPressed: false,
      boxSize: 200,
      numberSize: 24,
      position: {
        x: (width / 2) - 100,
        y: (height / 2) - 140,
      },
      initialPosition: {
        x: 0,
        y: 0,
      },
      randomNumber: null,
    };
    this.index = props.route.params.index;
    this._handlePanResponderMove = this._handlePanResponderMove.bind(this);
    this._handlePanResponderRelease = this._handlePanResponderRelease.bind(this);
    this._handlePanResponderStart = this._handlePanResponderStart.bind(this);
    this._panResponder = PanResponder.create({
      onStartShouldSetPanResponder: () => true,
      onPanResponderMove: this._handlePanResponderMove,
      onPanResponderRelease: this._handlePanResponderRelease,
      onPanResponderGrant: this._handlePanResponderStart,
      onPanResponderTerminate: this._handlePanResponderRelease,
    });
  }

  _handlePanResponderStart(evt, gestureState) {
    this.setState({
      isPressed: true,
      boxSize: 100,
      numberSize: 16,
      initialPosition: {
        x: gestureState.x0 - 50,
        y: gestureState.y0 - 140,
      },
    });
  }

  _handlePanResponderMove(evt, gestureState) {
    const newX = gestureState.moveX - 50;
    const newY = gestureState.moveY - 140;
    this.setState({
      position: {
        x: newX,
        y: newY,
      },
    });
  }

  _handlePanResponderRelease(evt, gestureState) {
    const numberOfSides = this.props.route.params.dice.numberOfSides;
    const randomNumber = Math.floor(Math.random() * numberOfSides) + 1;
    this.setState({
      isPressed: false,
      boxSize: 200,
      numberSize: 32,
      position: {
        x: gestureState.moveX - 100,
        y: gestureState.moveY - 180,
      },
      randomNumber: randomNumber,
    });
    this.props.route.params.onDiceRoll(randomNumber, this.index);
  }

  render() {
    let boxImage;
    const numberOfSides = this.props.route.params.dice.numberOfSides;
    if (numberOfSides === 4) {
      boxImage = require('../img/d4.png');
    } else if (numberOfSides === 6) {
      boxImage = require('../img/d6.png');
    } else if (numberOfSides === 12) {
      boxImage = require('../img/d12.png');
    }

    return (
      <ImageBackground source={require('../img/bkg.jpg')} style={styles.background}>
        <View style={styles.container}>
          <View
            {...this._panResponder.panHandlers}
            style={[styles.box, {
              width: this.state.boxSize,
              height: this.state.boxSize,
              left: Math.min(Math.max(this.state.position.x, 0), width - this.state.boxSize),
              top: Math.min(Math.max(this.state.position.y, 0), height - this.state.boxSize),
            }]}>
            <ImageBackground source={boxImage} style={{ width: '100%', height: '100%', borderRadius: 20 }}>
              <View style={{ flex: 1, justifyContent: 'center', alignItems: 'center' }}>
                <Text style={[styles.randomNumber, { fontSize: this.state.numberSize }]}>
                  {this.state.randomNumber}
                </Text>
              </View>
            </ImageBackground>
          </View>
        </View>
      </ImageBackground>
    );
  }
}

const styles = StyleSheet.create({
  background: {
    flex: 1,
    resizeMode: 'cover',
  },
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  box: {
    position: 'absolute',
    justifyContent: 'center',
    alignItems: 'center',
    overflow: 'hidden',
  },
  randomNumber: {
    color: 'white',
    fontWeight: 'bold',
  },
});