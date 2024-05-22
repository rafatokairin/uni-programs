import React from 'react';
import {
  View,
  Text,
  StyleSheet,
  TouchableWithoutFeedback,
  ScrollView,
  ImageBackground
} from 'react-native';

import CenterMessage from './CenterMessage';

export default class Abilities extends React.Component {
  navigate = (item) => {
    this.props.navigation.navigate('Ability', { ability: item });
  }

  render() {
    const { abilities } = this.props;
    return (
      <ImageBackground source={require('../img/bkg.jpg')} style={styles.background}>
        <ScrollView contentContainerStyle={[!abilities.length && { flex: 1 }]}>
          <View style={[!abilities.length && { justifyContent: 'center', flex: 1 }]}>
            {
              !abilities.length && <CenterMessage message='No abilities!' />
            }
            {
              abilities.map((item, index) => (
                <TouchableWithoutFeedback onPress={() => this.navigate(item)} key={index} >
                  <View style={styles.abilityContainer}>
                    <Text style={styles.ability}>{item.ability}</Text>
                  </View>
                </TouchableWithoutFeedback>
              ))
            }
          </View>
        </ScrollView>
      </ImageBackground>
    );
  }
}

const styles = StyleSheet.create({
  background: {
    flex: 1,
    resizeMode: 'cover',
  },
  abilityContainer: {
    padding: 16,
    borderBottomWidth: 2,
    borderBottomColor: 'rgba(0, 0, 0, .5)'
  },
  ability: {
    fontSize: 20,
    color: 'rgba(0, 0, 0, .5)'
  },
});