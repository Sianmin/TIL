"""
던더 메소드 (특별 메소드, 매직 메소드)

특별 메소드는 직접 호출하는 경우는 __init__말고는 거의 없다.

직접 호출보다는 len(), inter(), str() 등 관련된 내장함수를 호출하는 것이 훨씬 성능상 좋다.
파이썬 인터프리터가 알아서 최적의 호출 방법을 찾기 때문이다.

사용자 정의 속성을 만들 때 앞뒤로 이중 언더바를 가진 __foo__와 같은 형태의 속성명은 피하는 것이 좋다.
"""
import collections

Card = collections.namedtuple('Card', ['rank', 'suit'])

class FrenchDeck:
    ranks = [str(n) for n in range(2, 11)] + list('JQKA')
    suits = 'spades diamonds clubs hearts'.split()

    def __init__(self):
        self._cards = [Card(rank, suit) for suit in self.suits
                                        for rank in self.ranks]

    def __len__(self):
        return len(self._cards)

    def __getitem__(self, position):
        return self._cards[position]

suit_values = dict(spades=3, hearts=2, diamonds=1, clubs=0)
def spades_high(card):
    rank_value = FrenchDeck.ranks.index(card.rank)
    return rank_value * len(suit_values) + suit_values[card.suit]
if __name__ == '__main__':
    deck = FrenchDeck()
    for card in sorted(deck, key=spades_high):
        print(card)